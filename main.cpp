#include <fstream>
#include <iostream>

#include "ast.h"
#include "code_gen.h"
#include "obj_gen.h"

extern shared_ptr<NBlock> pb;
extern int yyparse();

int main() {
  cout << "===词法分析/语法分析===" << endl;
  yyparse();
  cout << "===抽象语法树===" << endl;
  pb->print("--");
  auto root = pb->jsonGen();
  cout << "===中间代码IR生成===" << endl;
  CodeGenContext ctx;
  ctx.generateCode(*pb);
  cout << "===目标代码生成===" << endl;
  ObjGen(ctx, "output.o");
  cout << "===AST JSON生成===" << endl;
  string json = "visual/ast.json";
  std::ofstream astJson(json);
  if (astJson.is_open()) {
    astJson << root;
    astJson.close();
    cout << "json write to " << json << endl;
  }
  return 0;
}