{
    'variables': {
    },
    "targets": [
        {
            "target_name": "node-windows-x64",
            "sources": [
                "src/ajanuw.cpp",
                "src/mem.hpp",
                "src/test.hpp",
                "src/invoke.hpp",
                "src/tools.hpp",
                "src/byte_table.hpp",
                "src/va_manage.cpp",
                "src/win32_gui.cpp",
                "src/main.cpp",
            ],
            "include_dirs": [
                "<!@(node -p \"require('node-addon-api').include\")",
                '<(module_root_dir)/deps/asmjit/include',
            ],
            'defines': ['NAPI_DISABLE_CPP_EXCEPTIONS'],
            'libraries': [
                '-l<(module_root_dir)/deps\\asmjit\\asmjit.lib',
            ],
            "copies": [
                {
                    "destination": "<(module_root_dir)/build/Release/",
                    "files": ["<(module_root_dir)/deps\\asmjit\\asmjit.dll"]
                }
            ]
        },
    ]
}
