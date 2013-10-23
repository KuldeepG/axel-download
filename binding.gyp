{
  'targets': [
    {
      'target_name': 'axelBinding',
      'sources': [
          './src/binding.cc',
          './src/wrapper.cc'
      ],
      'dependencies': [
        './vendor/libaxel/libaxel.gyp:libaxel'
      ]
    }
  ]
}
