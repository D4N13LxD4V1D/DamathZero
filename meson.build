project(
    'damath.ai',
    'cpp',
    default_options: ['cpp_std=c++23', 'warning_level=3'],
    meson_version: '>=1.5.1',
)

cpp_args = [
    '-Wunused',
    '-Wpedantic',
    '-Wself-assign',
    '-Wimplicit-fallthrough',
    '-Wctad-maybe-unsupported',
    '-Wmissing-prototypes',
    '-Wzero-as-null-pointer-constant',
    '-Wdelete-non-virtual-dtor',
    '--system-header-prefix=torch/',
    '--system-header-prefix=SFML/',
]

add_project_arguments(
    cpp_args,
    language: 'cpp',
)

deps = [
    dependency('torch', version: '2.2.0', modules: 'torch'),
    dependency('sfml', version: '2.6.1', modules: 'sfml'),
]
files = [
    'src/app/app.cc',
    'src/engine/agent.cc',
    'src/engine/arena.cc',
    'src/engine/coach.cc',
    'src/game/damath.cc',
    'src/neural/network.cc',
]
includes = ['src']

executable(
    'damath',
    'src/main.cc',
    files,
    include_directories: includes,
    dependencies: deps,
    install: true,
)