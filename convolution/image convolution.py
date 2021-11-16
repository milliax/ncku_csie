import numpy as np
import cv2
import imutils
import sys

# cv2.IMREAD_COLOR為imread的預設值，此參數亦可不加。
imageName = "hsuan.jpg"
image = cv2.imread(imageName, cv2.IMREAD_COLOR)
#若無指定圖片則結束程式。
if image is None:
    print("Could not open or find the image")
    sys.exit()

#縮小圖片到較適當尺寸。
#image = imutils.resize(image, height=450)
# 設定kernel size為5x5
kernel_size = 5
# 使用numpy建立 5*5且值為1/(5**2)的矩陣作為kernel。
#kernel = np.ones((kernel_size, kernel_size), dtype=np.float32) / kernel_size**2
kernel = np.array([[-1,-1,-1],[-1,8,-1],[-1,-1,-1]])

kernel2 = np.array((
        [-1, -2, -1],
        [0, 0, 0],
        [1, 2, 1]))

# 顯示矩陣內容，所有值皆為0.04的5x5矩陣
print(kernel)

# 使用cv2.filter2D進行convolute，
result = cv2.filter2D(image, -1, kernel)
b_sobel = cv2.filter2D(image,-1,kernel2)

print("showing the picture")
cv2.imshow("Filter", result)
cv2.imshow("Original", image)
# cv2.imwrite("sobel.jpg",b_sobel)
cv2.imshow("sobel",b_sobel)
cv2.waitKey(0)
