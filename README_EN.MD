# Ipari Script
![Image](https://github.com/user-attachments/assets/9376f1e2-51f4-46aa-bc27-7a73cbb29fbd)

**Ipari Script** is a dynamically-typed interpreter language designed to be easy to use, with concise syntax and a low barrier to entry.

## Overview

Originally created during high school as a study project, this interpreter language is **no longer in active development**. Beyond the features shown in the example files, there is very little additional functionality. The implementation is considered unstable for actual execution. Please use this for reference only.

**Key Details:**
- **Implementation Language:** C++
- **Runtime Environment:** Windows x86
- **License:** See badge above
- **First Released:** 2019/11/30
- **Source Code Uploaded:** 2023/05/27

## Language Features

### Output

Two output statements are supported in the console:
- `출력` (print): Simple output without newline
- `출력해` (println): Output followed by newline

Multiple outputs can be separated by commas:
```
출력해 '안녕, 이파리!'
출력해 '안녕하세요','^.^'
```

### Comments

Three comment styles are supported:
- `#` for single-line comments
- `#--` and `--#` for block comments (or `##...##`)

```
#This is a single-line comment
##This is a block
comment that spans
multiple lines##
```

### Block Structure

Ipari Script uses a unique block management system that improves upon both Python and traditional curly-brace languages:

- Blocks **automatically start** when using control statements (`만약`, `되풀이`) or function declarations
- Blocks **end with `end`**, but indentation (tab depth) before `end` determines which nested blocks close
- This allows closing multiple nested blocks simultaneously by adjusting tab indentation

**Ruby-style example:**
```
if true
  if true
  end
end
```

**Ipari-style equivalent:**
```
만일 참
  만일 참 # Tab:1
끝 # Tab:0
```

### Conditional Statements

Use `만약` (if), `아니고` (else if), and `아니면` (else):

```
가=입력("숫자 : ")
만약 가=10
  출력해 "가는 10임"
아니고 가=20
  출력해 "가는 20임"
아니면 출력해 "몰라 시벌"
끝
```

### Loops

**Range Loop** using `반복`:
```
반복 가=0~10:1
  출력해 가
끝
```

**Conditional Loop** using `되풀이` (executes while condition is true):
```
가=0
되풀이 가<10
  출력해 가
끝
```

### Functions

Declare functions with `함수`. Return values with `반환` or use `=` for single-line functions:

```
함수 더하기(가,나)=가+나
함수 더하기2(가,나)
    반환 가+나
끝
출력해 더하기(10,30) #Same as 더하기2(10,30)
```

## Language Influences

- 약속 (Yakpok), 와글 (Wagl)
- Ruby
- Python

## Not Implemented (Abandoned Features)

The following sections were planned but development was discontinued:
- Objects
- Constructors/Destructors
- Member variables & method access
- Using Ipari features
- Creating features
- Built-in functions
- Standard functions, file I/O, console, graphics (Winbgim), games (Dxlib)
- Syntax improvements, performance optimization, garbage collection
- Development tools

## Development Blog

Development logs and more information can be found at:
- https://blog.naver.com/banwonkim/221699253937
- https://blog.naver.com/banwonkim/221703112330
- https://blog.naver.com/banwonkim/221720351628
- https://blog.naver.com/banwonkim/221725177837
- https://cafe.naver.com/flashmkstore/1136
