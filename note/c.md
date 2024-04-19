## 1.初始化数组
> **总结**：始终先定义，再初始化就可以保证不出错。不管是不是变长数组。
### 1.1 使用栈内存
```
int len = 10; // 这里可以是scanf()输入的数值
int arr[len]; // 数组长度是变量，不能直接初始化
for(int i=0;i<len;i++) arr[i] = 0; // 变长数组定义后，再初始化
```
补充初始化的特例：使用`int arr[len]`定义的数组，且只需要成员全部初始化为0时，可以使用
```
memset(arr, 0, sizeof(arr)); // 只能初始化0，其他任何数都不能用此方法。
```

### 1.2 使用堆内存，malloc()
```
int len = 10; // 这里可以是scanf()输入的数值
int *arr = (int*)malloc(sizeof(int) * len);
for(int i=0;i<len;i++) arr[i] = 0;
free(arr);
```
## 2. 初始化二维数组
### 2.1 使用栈内存
```
int cols = 5; 
int rows = 3;
int matrix[rows][cols];
for(int i=0;i<rows;i++) for(int j=0;j<cols;j++) matrix[i][j] = 1;
```
### 2.2 使用堆内存
```
int rows = 5;
int cols = 3;
// 申请内存
int **matrix = (int**)malloc(sizeof(int *) * rows);
for(int i=0;i<rows;i++)
    matrix[i] = (int*)malloc(sizeof(int) * cols);
// 初始化
for(int i=0;i<rows;i++) for(int j=0;j<cols;j++) matrix[i][j] = 1;
```
