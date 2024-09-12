project(
    'damath.ai',
    'cpp',
    default_options: ['cpp_std=c++23'],
    meson_version: '>=1.5.1',
)

deps = []
files = []
includes = []

deps += [dependency('torch', version: '2.2.0', modules: 'torch')]

includes += ['src']

executable(
    'damath',
    'src/main.cc',
    files,
    include_directories: includes,
    dependencies: deps,
    install: true,
)
