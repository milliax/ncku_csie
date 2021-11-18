import cv2
import numpy as np

image = cv2.imread("../butterfly.jpg",0)

f = np.fft.fft2(image)
print(f)
f = 20*np.log(np.abs(f))

cv2.imshow("original",image)
cv2.imshow("transformed",f)
#cv2.waitKey(0)