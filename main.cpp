#include <fstream>
#include <iostream>

#include "ast.h"
#include "code_gen.h"
#include "obj_gen.h"

extern shared_ptr<NBlock> programBlock;
extern int yyparse();

int main() {
  yyparse();
  // std::cout << programBlock << std::endl;
  programBlock->print("--");
  auto root = programBlock->jsonGen();
  CodeGenContext context;
  //    createCoreFunctions(context);
  context.generateCode(*programBlock);
  ObjGen(context, "output.o");
  string jsonFile = "visualization/A_tree.json";
  std::ofstream astJson(jsonFile);
  if (astJson.is_open()) {
    astJson << root;
    astJson.close();
    cout << "json write to " << jsonFile << endl;
  }
  return 0;
}