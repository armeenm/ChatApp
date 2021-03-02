project('ChatApp',
  'cpp',
  version: '0.0.1',
  meson_version: '>=0.55.0',
  default_options: [
    'cpp_std=c++17',
    'buildtype=release',
    'b_ndebug=if-release',
    'warning_level=3',
    'b_lto=true',
    'pkg_config_path=' + meson.current_build_dir()
  ]
)

if get_option('use_conan')
  conan = find_program('conan')

  if get_option('buildtype').startswith('release')
    conan_bt = 'build_type=Release'
  else
    conan_bt = 'build_type=Debug'
  endif

  r = run_command(conan,
    'install', meson.current_source_dir(),
    '-if', meson.current_build_dir(),
    '-s', conan_bt,
    '--build=missing')

  if r.returncode() != 0
    error('Failed to install dependencies with Conan')
  endif
endif

fmt = dependency('fmt', include_type: 'system')
openssl = dependency('openssl', include_type: 'system')
cpr = dependency('cpr', include_type: 'system')
websocketpp = dependency('websocketpp', include_type: 'system')
asio = dependency('asio', include_type: 'system')
opus = dependency('opus', include_type: 'system')

### Sleepy-Discord ###

sd_flags = [
  '-DNONEXISTENT_UWEBSOCKETS=1',
  '-DEXISTENT_WEBSOCKETPP=1',
  '-DEXISTENT_OPUS=1',
  '-DEXISTENT_ASIO=1',
  '-DEXISTENT_CPR=1'
]

comp = meson.get_compiler('cpp')
if comp.get_argument_syntax() == 'msvc'
  ignore_warns = '/w'
else
  ignore_warns = '-w'
  add_project_arguments(
    '-Wshadow',
    '-Wconversion',
    '-Wlogical-op',
    '-Wduplicated-cond',
    '-Wduplicated-branches',
    '-Wformat=2',
    '-Wold-style-cast',
    '-Wuseless-cast',
    '-Wnull-dereference',
    language: 'cpp'
  )
endif

cmake = import('cmake')
sd_cmake_opts = cmake.subproject_options()
sd_cmake_opts.add_cmake_defines({'ONLY_SLEEPY_DISCORD': true})
sd_cmake_opts.append_compile_args('cpp', sd_flags, ignore_warns)

sd_proj = cmake.subproject('sleepy-discord', options: sd_cmake_opts)
sd_dep = declare_dependency(
  compile_args: sd_flags + [cpr.get_variable(pkgconfig: 'cflags')],
  link_args: [cpr.get_variable(pkgconfig: 'libs')],
  dependencies: sd_proj.dependency('sleepy-discord', include_type: 'system')
)

### Bot ###

executable('bot',
  'src/main.cpp',
  dependencies: [fmt, openssl, cpr, websocketpp, asio, opus, sd_dep],
  install: true
)
