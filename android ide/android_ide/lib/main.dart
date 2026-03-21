import 'package:flutter/material.dart';
import 'package:flutter_code_editor/flutter_code_editor.dart';
import 'package:flutter_highlight/themes/monokai-sublime.dart'; // 引入深色主題
import 'package:highlight/languages/java.dart'; // 引入 Java 語法解析

void main() {
  runApp(const MyTabletIDE());
}

class MyTabletIDE extends StatelessWidget {
  const MyTabletIDE({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Tablet IDE',
      debugShowCheckedModeBanner: false,
      home: const EditorScreen(),
    );
  }
}

class EditorScreen extends StatefulWidget {
  const EditorScreen({super.key});

  @override
  State<EditorScreen> createState() => _EditorScreenState();
}

class _EditorScreenState extends State<EditorScreen> {
  // 建立一個 CodeController 來管理程式碼狀態
  late final CodeController controller;

  @override
  void initState() {
    super.initState();
    // 初始化控制器，設定語言為 Java
    controller = CodeController(
      text: 'public class HelloWorld {\n  public static void main(String[] args) {\n    System.out.println("Hello, Tablet IDE!");\n  }\n}', // 預設程式碼
      language: java,
    );
  }

  @override
  void dispose() {
    controller.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: const Color(0xFF23241F), // 配合 Monokai 主題的背景色
      appBar: AppBar(
        title: const Text('我的平板 IDE (Java)'),
        backgroundColor: Colors.grey[900],
        foregroundColor: Colors.white,
        actions: [
          IconButton(
            icon: const Icon(Icons.save),
            onPressed: () {
              // 這裡可以取得使用者輸入的程式碼！
              String currentCode = controller.text;
              print("準備存檔：\n$currentCode");
              ScaffoldMessenger.of(context).showSnackBar(
                const SnackBar(content: Text('程式碼已記錄，準備實作存檔功能！')),
              );
            },
          ),
        ],
      ),
      // 使用 CodeTheme 來套用 Monokai 樣式
      body: CodeTheme(
        data: CodeThemeData(styles: monokaiSublimeTheme),
        child: SingleChildScrollView(
          child: CodeField(
            controller: controller,
            textStyle: const TextStyle(fontFamily: 'monospace', fontSize: 16),
            gutterStyle: const GutterStyle(
              textStyle: TextStyle(height: 1.5, color: Colors.grey), // 行號樣式
            ),
          ),
        ),
      ),
    );
  }
}