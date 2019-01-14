#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
@Author: Ling Bao
@Description: video read and write

@data: 2018/9/12
@version: V1.0.0
"""

import cv2


def video_capture(video_path, save_path):
    """
    读取视频并取帧
    :param video_path: 
    :param save_path:
    :return: 
    """
    v_cpa = cv2.VideoCapture(video_path)

    fps = v_cpa.get(cv2.CAP_PROP_FPS)
    size = (int(v_cpa.get(cv2.CAP_PROP_FRAME_WIDTH)), int(v_cpa.get(cv2.CAP_PROP_FRAME_HEIGHT)))
    total_count = v_cpa.get(cv2.CAP_PROP_FRAME_COUNT)

    print("fps: ", fps, "size: ", size, "count: ", total_count)

    count = 1000
    ret, frame = v_cpa.read()
    while ret:
        # cv2.namedWindow('video', cv2.WINDOW_NORMAL)
        # cv2.imshow("video", frame)

        # if cv2.waitKey(1) & 0xFF == ord('q'):
        #     break

        # 写文件
        if count % 10 == 0:
            image = cv2.cvtColor(frame)
            image = cv2.resize(image, (720, 1080))
            cv2.imwrite(save_path + str(count) + ".jpg", image)

            print('frame: %d' % count)

        ret, frame = v_cpa.read()
        count += 1

    v_cpa.release()
    cv2.destroyWindow()


if __name__ == "__main__":
    save_path_ = 'images/'
    video = "images/room.mp4"
    video_capture(video, save_path_)
