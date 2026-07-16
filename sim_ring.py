"""模拟环岛检测: 测试 RING_VALID_TH=80, RING_LOST_TH=8"""
import os, numpy as np
from PIL import Image

W, H = 188, 120
THRESHOLD = 15
JUMP_NUM = 3
SEARCH_RANGE = 10
SEARCH_MIN, SEARCH_MAX = 1, W-2

RING_VALID_TH = 80
RING_LOST_TH = 8

def calc_diff(x, y):
    return ((x - y) << 7) // (x + y)

def search_border(img):
    """简化的49.9边界搜索 (模拟实际管线)"""
    l_b = np.zeros(H, dtype=np.int16)
    r_b = np.full(H, W-1, dtype=np.int16)
    l_e = np.zeros(H, dtype=np.int8)
    r_e = np.zeros(H, dtype=np.int8)

    # 找最长白列参考点
    ref_col = W // 2

    # 简化: 直接逐行扫描
    for i in range(H-1, -1, -1):
        # 左边界: 从ref_col向左找第一个暗→亮跳变
        for j in range(ref_col, SEARCH_MIN, -1):
            if j + JUMP_NUM < W:
                d = calc_diff(img[i][j+JUMP_NUM], img[i][j])
                if d > THRESHOLD:
                    l_b[i] = j
                    l_e[i] = 1
                    break
        # 右边界: 从ref_col向右找
        for j in range(ref_col, SEARCH_MAX):
            if j - JUMP_NUM >= 0:
                d = calc_diff(img[i][j-JUMP_NUM], img[i][j])
                if d > THRESHOLD:
                    r_b[i] = j
                    r_e[i] = 1
                    break

    return l_b, r_b, l_e, r_e

def check_ring(img):
    l_b, r_b, l_e, r_e = search_border(img)
    l_cnt = np.sum(l_e)
    r_cnt = np.sum(r_e)

    r_ring = (l_cnt > RING_VALID_TH and r_cnt < RING_LOST_TH)
    l_ring = (r_cnt > RING_VALID_TH and l_cnt < RING_LOST_TH)

    return l_cnt, r_cnt, r_ring, l_ring, l_b, r_b, l_e, r_e

d = r"D:\new_document\Document\KEYU_AI8052U_OpenLibrary-main\KEYU_AI8052U_OpenLibrary-main\app_examples\yg_smartcar\simulation\photo\环岛（快入）"
for fname in sorted(os.listdir(d)):
    if not fname.endswith('.png'): continue
    img = Image.open(os.path.join(d, fname)).convert('L')
    img = img.resize((W, H), Image.LANCZOS)
    arr = np.array(img, dtype=np.uint8)
    lc, rc, rr, lr, lb, rb, le, re = check_ring(arr)
    status = ""
    if rr: status = "★ RIGHT RING"
    if lr: status = "★ LEFT RING"
    print(f"{fname[:35]:35s} L_valid={lc:3d} R_valid={rc:3d} {status}")
