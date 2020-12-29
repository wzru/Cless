
# Cless

编译原理实验的Toy Project——基于Flex、Bison、LLVM，使用C++实现的Cless（一种自定义语法的类C语言）语言编译器。

首先使用Flex & Bison对源代码进行parse；之后将AST输出为LLVM IR；最后调用LLVM后端接口，将IR编译成二进制目标代码。最终可以直接在目标操作系统上运行。

## Feature

本项目解析的是一种类C语言——Cless。支持的数据类型包括：void、int、float、double、char、string、bool、struct、多维数组。支持的语法包括：

- 变量的声明、初始化（暂不支持多维数组初始化）、赋值、二元运算
- 函数的定义、调用
- 外部函数（extern）声明和调用
- 控制语句if-else、for、while及其嵌套
- 单行注释（#）

## Usage

本项目已在WSL2的Ubuntu LTS 20.04 x64下，使用LLVM 10.0.0进行测试

使用说明

1. 编译Cless

```
make -j8
```

2. 运行测试

```
make test
```

3. 或者手动链接output.o生成可执行文件并运行

```
clang++ output.o -o test
./test
```

## Grammar


本编译器实现的语法是类似标准C的语法，主要的区别包括：
- 不需要在语句后面加分号;
- 数组定义和初始化语法不同
- if-else，for，while等语句块的大括号是必须
- 使用#来进行单行注释

## Test

1. 基本语法

```c
int func(int a, int b){
    if( a > b ){
        return func(b * 0.5)
    } else if( a == b ){
        return func(a * b)
    } else{
        return 0
    }
}

int main(int argc, string[1] argv){
    int i = 0
    for( ; i<argc; i=i+1){
        func(i, argc)
    }
    while( 1 ) {}
    return 0
}

```

2. 结构体使用

```c
struct Point {
    int x
    int y
}
int func(struct Point p) {
    return p.x
}
int test() {
    struct Point p
    p.x = 1
    p.y = 3
    func(p)
    return 0
}

```

3. 数组使用

```c
int testArray() {
    int[10] arr1 = [1,2,3,4]
    int[3][4] arr2
    int i, j
    for(i=0; i<3; i=i+1) {
        for(j=0; j<4; j=j+1) {
            arr2[i][j] = 0
        }
    }
    return 0
}
```

4. 外部函数调用

```c
extern int printf(string format)
extern int scanf(string format)

int testExtern() {
    string input
    scanf("%s", &input)
    printf("%d, %f, input = %s", 1, 0.1, input)
    return 0
}
```

------

## Reference

[LLVM Language Reference Manual](http://llvm.org/docs/LangRef.html)

[LLVM Tutorial](http://releases.llvm.org/10.0.0/docs/tutorial/index.html)

[stardust95/TinyCompiler](https://github.com/stardust95/TinyCompiler)