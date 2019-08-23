#include <iostream>
#include <ctime>
#include <unordered_map>
#include <memory>
#include <mutex>
#include <exception>

// Eigen 部分
#include <Eigen/Core>
// 稠密矩阵的代数运算（逆，特征值等）
#include <Eigen/Dense>

#define MATRIX_SIZE 50

/****************************
* 本程序演示了 Eigen 基本类型的使用
****************************/

class Locating {
public:
    Locating(int sparse) {
        std::cout << "init: " << sparse << std::endl;

        m_sparse = sparse;
    };

    int Run(int params) {
        return m_sparse;
    };

private:
    int m_sparse;
};

class TestPy {
public:

    void SetParams(int a) {
        test = a;
    };

    int TestEigen();

    int AddScene(int scene, int sparse);

    int Run(int scene, int params);

private:
    int test;
    std::mutex mu;

    std::unordered_map<int, std::shared_ptr<Locating>> scenes;
};

extern "C"{
    TestPy obj;

    void set_params_plus(int pa) {
        obj.SetParams(pa);
    }

    int test_eigen_plus() {
        return obj.TestEigen();
    }

    int test_add_scene(int scene, int sparse) {
        return obj.AddScene(scene, sparse);
    }

    int test_run(int scene, int params) {
        return obj.Run(scene, params);
    }
}
