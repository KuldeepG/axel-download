/***********************************************************************************\
* Axel-Download                                                                    *
*                                                                                  *
*  Description:                                                                    *
*  Node bindings for Axel ( Copyright 2001 Wilmer van der Gaast ) a lighter        *
*  download accelerator for Linux and other Unices                                 *
*                                                                                  *
*  Copyright (C) 2013  Kuldeep Ghogre                                              *
*                                                                                  *
*  This program is free software; you can redistribute it and/or modify            *
*  it under the terms of the GNU General Public License as published by            *
*  the Free Software Foundation; either version 2 of the License, or               *
*  (at your option) any later version.                                             *
*                                                                                  *
*  This program is distributed in the hope that it will be useful,                 *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of                  *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                   *
*  GNU General Public License for more details.                                    *
*                                                                                  *
*  You should have received a copy of the GNU General Public License along         *
*  with this program; if not, write to the Free Software Foundation, Inc.,         *
*  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.*                    *
\***********************************************************************************/

/* Wrapper */

#include "wrapper.h"

using namespace v8;

static void stop( int signal );

int run = 1;

/* For returning string values from functions*/
static char string[MAX_STRING];


Handle<Value> Download(const Arguments& args)
{
	HandleScope scope;
	conf_t conf[1];
	axel_t *axel;
	int i, cur_head = 0;
	String::Utf8Value utfStr(args[0]->ToObject()->Get(String::New("url"))->ToString());
  char* s = (char*) *utfStr; 
    
#ifdef I18N
	setlocale( LC_ALL, "" );
	bindtextdomain( PACKAGE, LOCALE );
	textdomain( PACKAGE );
#endif
	if( !conf_init( conf ) )
	{
		ThrowException(Exception::TypeError(String::New("Couldn't load configurations")));
		return scope.Close(Undefined());
	}
	
	opterr = 0;
	
	conf->add_header_count = cur_head;
	axel = axel_new( conf, 0, s );
	if( axel->ready == -1 )
	{
		axel_close( axel );
		ThrowException(Exception::TypeError(String::New("Could not parse URL")));
		return scope.Close(Undefined());
	}

	i = 0;
	s = axel->filename + strlen( axel->filename );
	while( 1 )
	{
		sprintf( string, "%s.st", axel->filename );
		if( access( axel->filename, F_OK ) == 0 )
		{
			if( axel->conn[0].supported )
			{
				if( access( string, F_OK ) == 0 )
					break;
			}
		}
		else
		{
			if( access( string, F_OK ) )
				break;
		}
		sprintf( s, ".%i", i );
		i ++;
	}
	
	if( !axel_open( axel ) )
	{
		ThrowException(Exception::TypeError(String::New("Could not open connection")));
		return scope.Close(Undefined());
	}
	
	axel_start( axel );

	axel->start_byte = axel->bytes_done;
	
	signal( SIGINT, stop );
	signal( SIGTERM, stop );
	
	while( !axel->ready && run )
	{
		long long int prev, done;
		
		prev = axel->bytes_done;
		axel_do( axel );
		
		done = ( axel->bytes_done / 1024 ) - ( prev / 1024 );
	}
			
	i = axel->ready ? 0 : 2;
	
	axel_close( axel );
	return scope.Close(Number::New(1));
}

/* SIGINT/SIGTERM handler						*/
void stop( int signal )
{
	run = 0;
}