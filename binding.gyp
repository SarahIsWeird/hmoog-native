{
    "targets": [
        {
            "target_name": "hmoog-native",
            "sources": [
                "src/native.cpp"
            ],
            "conditions": [
                ["OS=='win'", {
                    "sources": [
                        "src/native-win32.cpp"
                    ]
                }]
            ]
        }
    ]
}
