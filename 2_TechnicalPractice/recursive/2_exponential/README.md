## 004:2的幂次方表示

[原题目](http://cxsjsxmooc.openjudge.cn/2020t2spring2/002/)

- 总时间限制: 

  1000ms

- 内存限制: 

  65536kB

- 描述

  任何一个正整数都可以用2的幂次方表示。例如：  137=27+23+20同时约定方次用括号来表示，即ab可表示为a(b)。由此可知，137可表示为：  2(7)+2(3)+2(0)进一步：7=22+2+20（21用2表示）    3=2+20所以最后137可表示为：  2(2(2)+2+2(0))+2(2+2(0))+2(0)又如：  1315=210+28+25+2+1所以1315最后可表示为：  2(2(2+2(0))+2)+2(2(2+2(0)))+2(2(2)+2(0))+2+2(0)

- 输入

  一个正整数n（n≤20000）。

- 输出

  一行，符合约定的n的0，2表示（在表示中不能有空格）。

- 样例输入

  `137`

- 样例输出

  `2(2(2)+2+2(0))+2(2+2(0))+2(0)`

- 来源

  NOIP1998复赛 普及组 第一题