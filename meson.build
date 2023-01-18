project(
  'funk', 
  'cpp',
  version : '0.1',
  default_options : [
    'warning_level=3',
    'cpp_std=c++20'
  ]
)

include = include_directories('include')

executable(
  'main',
  sources: 'test/main.cpp',
  include_directories: include
)

funk_dep = declare_dependency(
  include_directories: include
)


unit_tests = [
  'Integer'
]

foreach name : tests 
  exe = executable(
    name, 'test' / name + '.cpp',
    include_directories: include
  )
  test(name, exe)
endforeach