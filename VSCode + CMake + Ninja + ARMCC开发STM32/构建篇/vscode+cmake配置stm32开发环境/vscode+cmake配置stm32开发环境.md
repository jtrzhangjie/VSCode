# vscode + cmake + ninja + ARMCC ����stm32��������������ƪ��

## 1. ǰ�û���

### 1.1 cmake��װ
- ��CMake����������CMake��װ�����а�װCMake��[CMake����](https://cmake.org/download/)
 ![alt text](image.png)
- ��װ���֮��ʹ��cmd�鿴cmake�Ƿ���ӽ��뻷��������
 ![alt text](image-1.png)

### 1.2 LLVM�׼���װ
- ��LLVM��github�����ط����氲װ�����а�װLLVM�׼���[LLVM](https://github.com/llvm/llvm-project/releases/tag/llvmorg-18.1.8)
  ![alt text](image-2.png)
- ��װ��ɺ��ֶ����`clang`�����������С�
  ![alt text](image-4.png)
- ʹ��cmd�鿴clang�Ƿ���ӽ��뻷��������
  ![alt text](image-3.png)

### 1.3 ninja��װ
- �ο�ninja��װ��[ninja��װ](https://blog.csdn.net/qq_36651243/article/details/115689930)
  
### 1.4 vscode�����װ
- ��vscode����г��а�װ���²����
  ![alt text](image-5.png)
  <mark>`clangd`�����`C/C++`������ܹ��棬��������ʹ��clangd��������Ƚ���`C/C++`���<mark>

### 1.5 ARMCC
- ARMCC��ӵ����������С�
  ![alt text](image-6.png)

### 1.6 ��ʹ�õ�stm32 mdk����
- ��Ҫ׼��һ������ʹ�õ�stm32 mdk���̡�
- ���̳�ʹ�õ������д�Ĺ��̣�Ҳ����ʹ��`stm32cubemx`���ɵĹ��̡�`stm32cubemx`���ɵĹ����м�ѡ������mdk���̡�
  
## 2. ����VScode���

### 2.1 ����clangd���
- clang�������ͼ�����������������ý��档
  ![alt text](image-7.png)
- ����`clangd`�ڱ�����·�������֮ǰ���ù��������������������`clangd`���ɣ����û�����ù���������������Ҫ������ɵ�·��
  ![alt text](image-8.png)
- ����`clangd`����������Ҫ�Ĳ�������`--compile_commands-dir`���˲�������ָ�����ɵ�`compile-commands.json`�ļ���ŵ�·�������ļ�����ȷ���������ļ���ת���Ӿ�ȷ��
  ![alt text](image-9.png)

### 2.2 ����CMake Tools���
- ����cmake���������ļ���ŵ�·��
  ![alt text](image-10.png)

## 3. ��дCmake�ļ�
### 3.1 ָ��������빤����
- �ڹ����ļ���Ŀ¼�£�����`armcc-toolchain.cmake`������ָ��ARMCC��������·��
  ![alt text](image-11.png)
- `armcc-toolchain.cmake`����
  ![alt text](image-12.png)
  ���ļ�ֻ��Ҫ�޸ĵ�һ�У�armcc�ı���·�����ɡ�

### 3.2 `CMakeLists.txt`�ļ���д
- �ڹ����ļ���Ŀ¼�£�����`CMakeLists.txt`�ļ�
  ![alt text](image-13.png)
- `CMakeLists.txt`�ļ�����
  - ��������
    ![alt text](image-14.png)
    ![alt text](image-18.png)
    ��Ҫ������cmake��Ͱ汾��Ŀ��ƽ̨��ϵͳ���ƣ�CPU���͡�<mark>`SYSTEM_NAM`һ��Ҫѡ��`Generic`<mark>��  

  - ����������
    ![alt text](image-15.png)

  - ������flag����
    ![alt text](image-16.png)

  - ͷ�ļ�·�����
    ![alt text](image-17.png)

  - ����ѡ��
    ![alt text](image-19.png)
    ��������Ҫ�ľ���ָ��`sct`�ļ�·�������ļ���Ҫ������keil��������һ�Ρ�
  
  - Դ�ļ�·�����
    ![alt text](image-20.png)  

  - Ŀ���ļ�����
    ![alt text](image-21.png)

  - hex��bin�ļ�����
    ![alt text](image-22.png)

### 3.3 `CMakePresets.json`�ļ���д
- ��������ninja
  ![alt text](image-23.png)

## 4. ʹ��
### 4.1 ����������
![alt text](image-25.png)
`CMakeLists.txt`�ļ��ڱ�д�����н��б��棬�ͻ��Զ��������ù�����������ͼ���ʾ����������������

### 4.2 ���̹���
![alt text](image-24.png)
����·����֣����б���
![alt text](image-26.png)
��ͼΪ����ɹ�֮��Ľ�ͼ�����Կ�����ش洢ռ�ô�С��Ϣ��Ҳ�ܿ���������ʱ3.5s��ʹ��mdk���й��̱�����룬��Ҫ1�������ϡ�