#ifndef _TRAIL_H_
#define _TRAIL_H_

#include "ky_headfile.h"

#define CENTER_POINT 65
#define EDGE_IGNORE 7
#define MIN_WHITE_LENGTH 3

#define PICTURE_LENGTH 64
#define BROKEN_LENTH 32

typedef enum TRACK_ELEMENT
{
    NONE,          // ��
    START,         // ���
    STRAIGHT,      // ֱ��
    RIGHT_ANGLE_l, // ��ֱ�����
    RIGHT_ANGLE_r, // ��ֱ�����
    // TURN,         // ��������
    RING_l,     // ��������
    RING_r,     // �һ�������
    RING_c,     // ��������
    CROSS,      // ʮ�ֽ���·��
    BROKEN,     // ��·����
    BROKEN_RODE // ��·
} TRACK_ELEMENT;

#endif