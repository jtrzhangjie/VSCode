# vscode + cmake + ninja + ARMCC ����stm32��������������ƪ��

## 1. ǰ�û���
### 1.1 JLink�׼���װ
- ��Segger����������Jlink�׼���װ�����а�װJlink��[Jlink](https://www.segger.com/downloads/jlink/)
  ![alt text](image.png)

### 1.2 vscode�ĵ��Բ����װ
- ��vscode����г��а�װ`Cortex-Debug`���
![alt text](image-1.png)
- �������ý��棬����`Cortex-debug`���������
  ![alt text](image-10.png)
- ����`Jlink GDBServer`·�� 
  ![alt text](image-11.png) 
  ![alt text](image-12.png)  
- �����޸�
  
  
## 2. ����
- ʹ��֮ǰ[����ƪ](https://blog.csdn.net/qq_15301285/article/details/141159657)�Ĺ��̣�����ͼ��CMake������ܽ��г���ı��롣
  ![alt text](image-2.png)

## 3. ����
- ��debug���棬ѡ��`create a launch.json file`�����������ļ���
  ![alt text](image-3.png)
- ���ļ���ѡ��`Add Configuration...`
  ![alt text](image-4.png)
- �ڵ�������ѡ��`Cortex Debug: Jlink`��������ʹ�õ���`Jlink`���е��ԣ�ͬ��Ҳ��ʹ��`stlink`����`openOCD`��
  ![alt text](image-5.png)
- �ڴ���������ģ���н����޸ĺ��������ݡ�
  ![alt text](image-6.png)
  ![alt text](image-7.png)
  ������Ҫ�����¼�������޸ĺ�������
  - `"executable":`����Ŀ����������д֮ǰ�������ɵ�elf�ļ�����λ��
  - `"interface":`����Ŀ������������ָ������ʹ�õĽӿ�Э�飬`jtag`����`swd`
  - `"device":`����Ŀ����������ָ�����Ե�MCU�ͺţ�`�����jlink���޷��ҵ��Լ�ʹ�õ�MCU�����������MCU��Jlink�У���������߽���ָ��`
  - `"svdFile":`����Ŀ��������ָ��svd�ļ���λ�ã����ļ������ڵ��Թ����в鿴�Ĵ��������û�д��ļ������޷��鿴�Ĵ�������
- �޸����֮�󣬱��棬����debug���棬ѡ��`Debug with JLink`������Խ���
  ![alt text](image-8.png)
  ![alt text](image-9.png)