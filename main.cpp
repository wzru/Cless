#include <fstream>
#include <iostream>

#include "ast.h"
#include "code_gen.h"
#include "obj_gen.h"

extern shared_ptr<NBlock> pb;
extern int yyparse();

int main() {
  yyparse();
  pb->print("--");
  auto root = pb->jsonGen();
  CodeGenContext ctx;
  ctx.generateCode(*pb);
  ObjGen(ctx, "output.o");
  string json = "visual/ast_tree.json";
  std::ofstream astJson(json);
  if (astJson.is_open()) {
    astJson << root;
    astJson.close();
    cout << "json write to " << json << endl;
  }
  return 0;
}