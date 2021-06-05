{
    'variables': {},
    "targets": [
        {
            "target_name":
            "node-windows-x64",

            # https://chromium.googlesource.com/external/skia/gyp/+/6b0b63f3d444e68d91f6c3b066e1597f18db05a9/common_conditions.gypi
            'msvs_settings': {
                "VCCLCompilerTool": {
                    'WarningLevel': '4',
                    "AdditionalOptions": [
                       "/EHsc",
                       "/std:c++latest",
                    ],
                }
            },
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
                "src/_util.hpp",

                # Flex Bison
                "src/ces/lexer.cc",
                "src/ces/parser.h",
                "src/ces/parser.cc",
                "src/ces/BaseNode.h",
                "src/ces/BaseNode.cpp",
                "src/ces/export.h",
                "src/ces/export.cpp",
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
