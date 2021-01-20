## WebEngine Markdown Editor Example

This example uses [QWebEngineView](http://doc.qt.io/qt-5/qwebengineview.html)
to preview text written using the [Markdown](https://en.wikipedia.org/wiki/Markdown)
syntax.

### Acknowledgments

The conversion from Markdown to HTML is done with the help of the
[marked JavaScript library](https://github.com/chjj/marked) by _Christopher Jeffrey_.
The [style sheet](https://kevinburke.bitbucket.io/markdowncss/)
was created by _Kevin Burke_.

## Compiler Reordering:

```cpp
int A, B;

void foo()
{
    A = B + 1;
    B = 0;
}
```

```x86asm
//x86-64 gcc 10.2 -std=gnu++11 -Wall -Wextra  -O3
foo():
        mov     eax, DWORD PTR B[rip]
        mov     DWORD PTR B[rip], 0
        add     eax, 1
        mov     DWORD PTR A[rip], eax
        ret
B:
        .zero   4
A:
        .zero   4
```

