#include<stdio.h>
#include<string.h>

#define Maxsize 10007

const char* rwtab[6] = { "begin","if","then","while","do","end" };//关键字表
char ch;//字符变量，存放最新读入的源程序字符
char chStream[Maxsize];//缓存输入的字符流
char strToken[Maxsize];//存放构成单次符号的字符串
int p, syn, sum;

//把下一个字符读入ch
char GetChar(int* p)
{
    return chStream[(*p)++];
}

//跳过空白符，直至读入一个非空字符
char GetBC(int* p)
{
    while (chStream[*p] == ' ') {
        (*p)++;
    }
    return chStream[(*p)++];
}


// 判断是否为字母 
int IsLetter(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
        return 1;
    }
    return 0;
}

// 判断是否为数字
int IsDigit(char c)
{
    if (c >= '0' && c <= '9') {
        return 1;
    }
    return 0;
}

// 搜索指针回调一个字符位置 
void Retract(int* p)
{
    (*p)--;
}

// 运算符和界符的判断


void solve(int* p)
{
    memset(strToken, 0, sizeof(strToken));
    ch = GetBC(p); // 跳过空白符，直至读入一个非空字符
    if (IsLetter(ch)) { // 第一个是字母，则可能是关键字也可能是标识符 
        int idx = 0;
        while (IsLetter(ch) || IsDigit(ch)) {
            strToken[idx++] = ch;
            ch = GetChar(p);
        }
        //        strToken[idx] = '\0';
        Retract(p); // 搜索指针回调一个字符位置 
        syn = 10; // 先默认是标识符，接下来再判断是否为关键字
        for (int i = 0; i < 6; i++) {
            if (strcmp(strToken, rwtab[i]) == 0) { // 与关键字相比较 
                syn = i + 1; // 获取对应关键字的种别 
                break;
            }
        }
    }
    else if (IsDigit(ch)) { // 第一个是数字 
        sum = 0;
        while (IsDigit(ch)) {
            sum = sum * 10 + (ch - '0');
            ch = GetChar(p);
        }
        Retract(p);
        syn = 11;
    }
    else {
        switch (ch) {
        case '+': syn = 13; strToken[0] = ch; break;
        case '-': syn = 14; strToken[0] = ch; break;
        case '*': syn = 15; strToken[0] = ch; break;
        case '/': syn = 16; strToken[0] = ch; break;
        case ':':
            syn = 17;
            strToken[0] = ch;
            ch = GetChar(p); // 超前搜索一个字符 
            if (ch == '=') {
                strToken[1] = ch;
                syn = 18;
            }
            else {
                // 如果超前搜索到的字符不能与当前字符相结合，则需要回退 
                Retract(p);
            }
            break;
        case '<':
            syn = 20;
            strToken[0] = ch;
            ch = GetChar(p);
            if (ch == '>') {
                strToken[1] = ch;
                syn = 21;
            }
            else if (ch == '=') {
                strToken[1] = ch;
                syn = 22;
            }
            else {
                Retract(p);
            }
            break;
        case '>':
            syn = 23;
            strToken[0] = ch;
            ch = GetChar(p);
            if (ch == '=') {
                strToken[1] = ch;
                syn = 24;
            }
            else {
                Retract(p);
            }
            break;
        case '=': syn = 25; strToken[0] = ch; break;
        case ';': syn = 26; strToken[0] = ch; break;
        case '(': syn = 27; strToken[0] = ch; break;
        case ')': syn = 28; strToken[0] = ch; break;
        case '#': syn = 0; strToken[0] = ch; break;
        default: syn = -1; break;
        }
    }
}

int main()
{
    int idx = 0;
    do {
        ch = getchar();
        chStream[idx++] = ch;
    } while (ch != '#');
    chStream[idx] = '\0'; // 标记字符串结束

    p = 0;
    do {
        solve(&p);
        switch (syn) {
        case -1: printf("error!\n"); break;
        case 11: printf("<%d, %d>\n", syn, sum); break;
        default:
            printf("<%d, %s>\n", syn, strToken);
            break;
        }
    } while (p < idx && syn != 0);


    return 0;
}