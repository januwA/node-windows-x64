{
    "targets": [
        {
            "target_name": "node-windows-x64",
            "sources": [
                "src/_utils.cpp",
                "src/mem.hpp",
                "src/test.hpp",
                "src/invoke.hpp",
                "src/tools.hpp",
                "src/byte_table.hpp",
                "src/va_manage.cpp",
                "src/main.cpp",
            ],
            "include_dirs": [
                "<!@(node -p \"require('node-addon-api').include\")"
            ],
            'defines': ['NAPI_DISABLE_CPP_EXCEPTIONS'],
        }
    ]
}
