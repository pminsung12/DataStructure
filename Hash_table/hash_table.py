
import numpy as np

values = [512, 1, 513, 515, 4, 6, 7, 522, 524, 13, 525, 527, 535, 536, 541, 557, 560, 50, 56, 571, 574, 577, 580, 68, 583, 72, 77, 79, 81, 601, 89, 613, 614, 616, 110, 113, 628, 116, 121, 130, 135, 654, 658, 163, 677, 681, 173, 686, 692, 182, 705, 194, 716, 205, 722, 727, 217, 730, 734, 226, 742, 743, 753, 755, 757, 245, 252, 265, 778, 268, 274, 275, 795, 798, 301, 817, 818, 307, 829, 831, 833, 321, 324, 332, 845, 339, 342, 854, 858, 348, 353, 354, 360, 361, 362, 876, 365, 881, 376, 888, 894, 895, 896, 897, 387, 389, 390, 395, 398, 911, 913, 407, 920, 921, 412, 925, 418, 932, 936, 937, 940, 434, 439, 442, 956, 446, 958, 449, 968, 970, 461, 463, 977, 992, 491, 496, 503]
mod


arr = np.array(values)
mod = arr%500


d = dict()#key값 충돌을 알아보는 dic
for i in mod:
    if i not in d:
        d[i]=1
    else:
        d[i]+=1


#key를 value로 저장, 여기서 value들의key는 나머지 값이 됨
#나머지값이 겹칠 때 즉 지금 딕셔너리의 키가 2일 때 

count = -1
table = dict()
for i in mod:
    count += 1
    while(1):#충돌했을 때 선형조사법 사용
        if  i not in table:
            table[i] = arr[count]
            break
        else:
            i += 1
new_dict = sorted(table.items(), key=lambda x:x[0], reverse=False)
new_dict






