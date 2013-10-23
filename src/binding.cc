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

/* Node Bindings */

#include <node.h>
#include <v8.h>
#include "wrapper.h"

using namespace v8;

void Init(Handle<Object> exports, Handle<Object> module) {
  module->Set(String::NewSymbol("exports"),
      FunctionTemplate::New(Download)->GetFunction());
}

NODE_MODULE(axelBinding, Init)