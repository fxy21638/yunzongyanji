/*
 * ��Ŀ���ƣ�[STC32G144K246��Դ��] ��Դ�����
 * ��Ȩ���У�[2025] [��������ͨ���Ƽ����޹�˾]
 *
 * ����Э�飺���� GNU GPL v3.0 ��Դ����
 * ��������Э����ж��ο��������������뱣��ԭʼ��Ȩ��Ϣ
 * Э������μ���https://www.gnu.org/licenses/gpl-3.0.html
 *
 * �������������������ṩ�����ο���ʹ�÷���������֤������
 *
 * Э���ļ���GPL v3.0 �����ı�λ�ڸ�Ŀ¼��
 *
 * === �ļ���Ϣ ===
 * �ļ�����[ky_typedef.h]
 * ������λ����������ͨ���Ƽ����޹�˾
 * ���û�����[Keil MDK 5.36 / STCϵ�е�Ƭ��]
 * �ٷ�������
 *   -
 * ����ֿ⣺[https://gitee.com/beijing-keyu---jiangxi/KEYU_AI8052U_OpenLibrary]
 *   - �Ա����̣�https://kyznc.taobao.com/
 *   - ����֧�֣�QQȺ 974530818
 *
 * === �޶���¼ ===
 * ����       |  ������  | ���˵��
 * -----------|----------|----------------------
 * 2025.12.22 |   xiao   | V2.0
 */
#ifndef __KY_TYPEDEF_H__
#define __KY_TYPEDEF_H__

#include <stdio.h>
#include "ky_assert.h"

// ����״̬ö��

// ״̬ö��
typedef enum { ERROR = 0, SUCCESS = 1 } Status;


typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint32_t;

typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int32_t;

typedef uint8_t far image_t;

#endif
