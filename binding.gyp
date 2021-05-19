{
    'variables': {},
    "targets": [
        {
            "target_name":
            "node-windows-x64",
            "sources": [
                "src/ajanuw.cpp",
                "src/createThread.hpp",
                "src/mem.hpp",
                "src/target.hpp",
                "src/test.hpp",
                "src/invoke.hpp",
                "src/tools.hpp",
                "src/byte_table.hpp",
                "src/va_manage.cpp",
                "src/win32_gui.cpp",
                "src/global_define.hpp",
                "src/main.cpp",
            ],

            # headers
            "include_dirs": [
                "<!@(node -p \"require('node-addon-api').include\")",
                '<(module_root_dir)/include',
            ],
            'defines': ['NAPI_DISABLE_CPP_EXCEPTIONS'],

            # link libs
            'link_settings': {
                'library_dirs': [
                    # '<(module_root_dir)/deps_release/lib',
                ],
                'libraries': [
                    # '-lasmjit.lib', '-lasmtk.lib',
                    '-l<(module_root_dir)/deps_release/lib/**',
                ],
            },

            # Copy the dll after packaging
            "copies": [{
                "destination": "<(module_root_dir)/build/Release/",
                "files": ["<(module_root_dir)/deps_release/dll/**"]
            }]
        },
    ]
}
