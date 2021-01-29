project(
    'libtide',
    'cpp', 
    version : '0.1.1',
    license : 'MIT',
    meson_version : '>=0.55',
    default_options : [
        'cpp_std=c++17',
        'warning_level=3'
    ]
)

# Declare a dependency so this can be used as a subproject.
libtide_dep = declare_dependency(
    include_directories : 'include',
    version : meson.project_version()
)
