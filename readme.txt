1. 问题： 顶层Make和下层make不能很好兼容
   上层Makefile调用下层时一些特殊变量需要注意，如pwd
   上层调用时下层的$(PWD)会被当做上层文件路径，
   需要改为$$(pwd)这句话的意思是当上层调用时会被解析为$(pwd)，
   真正进入下层目录是就会被正确解析为下层目录的当前目录


   the doucument is a relief of what pro is used to do and how it been made up 

   1. the pro is a transform of IFSF protocal which is often used in petro 
   server station and some others .

   practise is the first of all to grow on skil of computer technology, how to 
   make sence of this, <apue> is a good tool book in linux c code skill.

   this porgram is based on FCC of css.Ld that I work in.

   2. when you get the code, please record 