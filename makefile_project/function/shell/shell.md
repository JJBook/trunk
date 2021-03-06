shell函数不同于除“wildcard”函数之外的其它函数。make可以使用它来和外部通信。

函数功能：函数“shell”所实现的功能和shell中的引用（``）相同。实现对命令的扩展。这就意味着需要一个shell 命令作为此函数的参数，函数的返回结果是此命令在shell中的执行结果。make仅仅对它的返回结果进行处理；make将函数返回结果中的所有换行符（“\n”）或者一对“\n\r”替换为单空格；并去掉末尾的回车符号（“\n”）或者“\n\r”。进行函数展开式时，它所调用的命令（它的参数）得到执行。除对它的引用出现在规则的命令行和递归变量的定义中以外，其它决大多数情况下，make是在读取解析Makefile时完成对函数shell的展开。

返回值：函数“shell”的参数（一个shell命令）在shell环境中的执行结果。

函数说明：函数本身的返回值是其参数的执行结果，没有进行任何处理。对结果的处理是由make进行的。当对函数的引用出现在规则的命令行中，命令行在执行时函数才被展开。展开时函数参数（shell命令）的执行是在另外一个shell进程中完成的，因此需要对出现在规则命令行的多级“shell”函数引用需要谨慎处理，否则会影响效率（每一级的“shell”函数的参数都会有各自的shell进程）。

示例1：
```makefile
contents := $(shell cat foo)
```

将变量“contents”赋值为文件“foo”的内容，文件中的换行符在变量中使用空格代替。

示例2：
```makefile
files := $(shell echo *.c)
```

将变量“files”赋值为当前目录下所有.c文件的列表（文件名之间使用空格分割）。在shell中之行的命令是“echo *.c”，此命令返回当前目录下的所有.c文件列表。上例的执行结果和函数“$(wildcard *.c)”的结果相同，除非你使用的是一个奇怪的shell。
注意：通过上边的两个例子我们可以看到，当引用“shell”函数的变量定义使用直接展开式定义时，可以保证函数的展开是在make读入Makefile时完成。后续对此变量的引用就不会有展开过程。这样就可以避免规则命令行中的变量引用在命令行执行时展开的情况发生（因为展开“shell”函数需要另外的shell进程完成，影响命令的执行效率）。这也是我们建议的方式。

```makefile
# we want bash as shell
#SHELL := $(shell if [ -x "$$BASH" ]; then echo $$BASH; \
#   else if [ -x /bin/bash ]; then echo /bin/bash; \
#   else echo sh; fi; fi)
SHELL1 := $(shell if [ -x "$$SHELL" ]; then echo $$SHELL; \
    else echo 123; fi)
#makefile中
#1.怎样执行shell 命令: $(shell xxx),xxx部分就是shell script的具体内容;注意，在shell函数中调用变量时,需要使用 $$变量名
#2.makefile可以接受环境变量,例如在外面设置环境变量AAA,在makefile中能获取到;
$(info ${SHELL1})
$(info ${AAA})
```
