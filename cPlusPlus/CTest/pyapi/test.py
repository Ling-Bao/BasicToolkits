from ctypes import *
eigen_testing = CDLL('lib/libeigenMatrix.so')

eigen_testing.set_params_plus(666)
eigen_testing.test_eigen_plus()

eigen_testing.test_add_scene(1, 10001)
eigen_testing.test_add_scene(2, 10002)
eigen_testing.test_add_scene(3, 10003)
eigen_testing.test_add_scene(4, 10004)
eigen_testing.test_add_scene(5, 10005)

eigen_testing.test_run(1, 23)
eigen_testing.test_run(2, 233)
eigen_testing.test_run(3, 2333)
