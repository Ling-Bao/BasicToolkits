#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Create on 14/1/2019
@Author: Ling Bao

@Description: Compute SSIM, MSE and PSNR
"""


class ImgEva:
    def gaussian_2d(self, shape=(3, 3), sigma=0.5):
        """
        生成二维高斯核
        :param shape: 
        :param sigma: 高斯核半径
        :return: 
        """
        m, n = [(s - 1.) / 2. for s in shape]
        y, x = np.ogrid[-m:m + 1, -n:n + 1]

        h = np.exp(-(x * x + y * y) / (2. * sigma * sigma))
        h[h < np.finfo(h.dtype).eps * h.max()] = 0
        sum_h = h.sum()

        if sum_h != 0:
            h /= sum_h
        return h

    def filter_2d(self, x, kernel, mode='same'):
        """
        二维卷积
        :param x: 
        :param kernel: 二维高斯核
        :param mode: 指定padding方式
        :return: 
        """
        return convolve2d(x, np.rot90(kernel, 2), mode=mode)

    def ssim(self, im1, im2, k1=0.01, k2=0.03, win_size=11, L=255):
        if not im1.shape == im2.shape:
            raise ValueError("Input images must have the same dimensions")
        if len(im1.shape) > 2:
            raise ValueError("Please input the images with 1 channel")

        M, N = im1.shape
        C1 = (k1 * L) ** 2
        C2 = (k2 * L) ** 2
        window = self.gaussian_2d(shape=(win_size, win_size), sigma=1.5)
        window = window / np.sum(np.sum(window))

        if im1.dtype == np.uint8:
            im1 = np.double(im1)
        if im2.dtype == np.uint8:
            im2 = np.double(im2)

        mu1 = self.filter_2d(im1, window, 'valid')
        mu2 = self.filter_2d(im2, window, 'valid')
        mu1_sq = mu1 * mu1
        mu2_sq = mu2 * mu2
        mu1_mu2 = mu1 * mu2
        sigma1_sq = self.filter_2d(im1 * im1, window, 'valid') - mu1_sq
        sigma2_sq = self.filter_2d(im2 * im2, window, 'valid') - mu2_sq
        sigmal2 = self.filter_2d(im1 * im2, window, 'valid') - mu1_mu2

        ssim_map = ((2 * mu1_mu2 + C1) * (2 * sigmal2 + C2)) / ((mu1_sq + mu2_sq + C1) * (sigma1_sq + sigma2_sq + C2))

        return np.mean(np.mean(ssim_map))

    def ssim_diff(self, im1, im2):
        shape1 = im1.shape
        shape2 = im2.shape

        min_h = np.min([shape1[0], shape2[0]])
        min_w = np.min([shape1[1], shape2[1]])

        # new_im1 = im1[0:min_h, 0:min_w]
        # new_im2 = im2[0:min_h, 0:min_w]
        #
        # ssim_res1 = self.ssim(new_im1, new_im2)

        new_im3 = im1[(shape1[0] - min_h)//2:(shape1[0] + min_h)//2, (shape1[1] - min_w)//2:(shape1[1] + min_w)//2]
        new_im4 = im2[(shape2[0] - min_h)//2:(shape2[0] + min_h)//2, (shape2[1] - min_w)//2:(shape2[1] + min_w)//2]

        ssim_res2 = self.ssim(new_im3, new_im4)

        # ssim_res = (ssim_res1 + ssim_res2) / 2

        return ssim_res2

    def psnr(self, im1, im2):
        if not im1.shape == im2.shape:
            raise ValueError("Input images must have the same dimensions")
        if len(im1.shape) > 2:
            raise ValueError("Please input the images with 1 channel")

        if im1.dtype == np.uint8:
            im1 = np.double(im1)
        if im2.dtype == np.uint8:
            im2 = np.double(im2)

        B = 8
        MAX = 2 ^ B - 1
        h, w = im1.shape
        MSE = (np.abs(im1 - im2) * np.abs(im1 - im2)).sum() / (h * w)  # 均方差

        PSNR = 20 * np.log10(MAX / np.sqrt(MSE))  # 峰值信噪比

        return MSE, PSNR

    def psnr_diff(self, im1, im2):
        shape1 = im1.shape
        shape2 = im2.shape

        min_h = np.min([shape1[0], shape2[0]])
        min_w = np.min([shape1[1], shape2[1]])

        new_im1 = im1[(shape1[0] - min_h) // 2:(shape1[0] + min_h) // 2,
                  (shape1[1] - min_w) // 2:(shape1[1] + min_w) // 2]
        new_im2 = im2[(shape2[0] - min_h) // 2:(shape2[0] + min_h) // 2,
                  (shape2[1] - min_w) // 2:(shape2[1] + min_w) // 2]

        return self.psnr(new_im1, new_im2)


def test_ssim_same():
    image_path1 = 'data/image1.jpeg'
    image_path2 = 'data/image2.jpeg'

    img1 = cv2.imread(image_path1, 0)
    img2 = cv2.imread(image_path2, 0)

    imgEva = ImgEva()

    t1 = time.time()
    ssim_res = imgEva.ssim(np.array(img1), np.array(img2))
    t2 = time.time()
    print(round(ssim_res, 3), round(t2 - t1, 3))


def test_ssim_diff():
    image_path1 = 'data/image1.jpg'
    image_path2 = 'data/image1.jpeg'

    img1 = cv2.imread(image_path1, 0)
    img2 = cv2.imread(image_path2, 0)

    t1 = time.time()
    imgEva = ImgEva()
    ssim_res = imgEva.ssim_diff(img1, img2)
    t2 = time.time()
    print(round(ssim_res, 3), round(t2 - t1, 3))


def test_psnr_same():
    image_path1 = 'data/image1.jpg'
    image_path2 = 'data/image2.png'

    img1 = cv2.imread(image_path1, 0)
    img2 = cv2.imread(image_path2, 0)

    t1 = time.time()
    imgEva = ImgEva()
    mse_res, psnr_res = imgEva.psnr(img1, img2)
    t2 = time.time()
    print(round(mse_res, 3), round(psnr_res, 3), round(t2 - t1, 3))


def test_psnr_diff():
    image_path1 = 'data/image2.png'
    image_path2 = 'data/image2.jpeg'

    img1 = cv2.imread(image_path1, 0)
    img2 = cv2.imread(image_path2, 0)

    t1 = time.time()
    imgEva = ImgEva()
    mse_res, psnr_res = imgEva.psnr_diff(img1, img2)
    t2 = time.time()
    print(round(mse_res, 3), round(psnr_res, 3), round(t2 - t1, 3))


if __name__ == '__main__':
    # test_ssim_same()

    # test_ssim_diff()

    # test_psnr_same()

    test_psnr_diff()
