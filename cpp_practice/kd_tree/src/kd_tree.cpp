#include <pcl/point_cloud.h>
#include <pcl/kdtree/kdtree_flann.h>

#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

int
main(int argc, char** argv)
{
    // 种下随机数种子
    srand(time(NULL));

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);

    // 用随机数，随机生成1000个点的无序点云
    cloud->width = 1000;
    cloud->height = 1;
    cloud->points.resize(cloud->width * cloud->height);

    for (size_t i = 0; i < cloud->points.size(); ++i)
    {
        cloud->points[i].x = 1024.0f * rand() / (RAND_MAX + 1.0f);          // c++中rand()函数生成的范围:0~RAND_MAX，
        cloud->points[i].y = 1024.0f * rand() / (RAND_MAX + 1.0f);
        // cloud->points[i].z = 1024.0f * rand() / (RAND_MAX + 1.0f);
        cloud->points[i].z = 0;
    }

    // 初始化kdTree
    pcl::KdTreeFLANN<pcl::PointXYZ> kdtree;
    // 设置要搜索的点云
    kdtree.setInputCloud(cloud);

    pcl::PointXYZ searchPoint;

    searchPoint.x = 1024.0f * rand() / (RAND_MAX + 1.0f);
    searchPoint.y = 1024.0f * rand() / (RAND_MAX + 1.0f);
    // searchPoint.z = 1024.0f * rand() / (RAND_MAX + 1.0f);
    searchPoint.z = 0;
    // K近邻搜索

    int K = 5;

    std::vector<int> pointIdxNKNSearch(K);
    std::vector<float> pointNKNSquaredDistance(K);

    std::cout << "K nearest neighbor search at (" << searchPoint.x
        << " " << searchPoint.y
        << " " << searchPoint.z
        << ") with K=" << K << std::endl;

    if (kdtree.nearestKSearch(searchPoint, K, pointIdxNKNSearch, pointNKNSquaredDistance) > 0)
    {
        for (size_t i = 0; i < pointIdxNKNSearch.size(); ++i)
            std::cout << "    " << cloud->points[pointIdxNKNSearch[i]].x
            << " " << cloud->points[pointIdxNKNSearch[i]].y
            << " " << cloud->points[pointIdxNKNSearch[i]].z
            << " (squared distance: " << sqrt(pointNKNSquaredDistance[i]) << ")" << std::endl;
    }

    // 以radius为半径的范围搜索

    std::vector<int> pointIdxRadiusSearch;
    std::vector<float> pointRadiusSquaredDistance;

    float radius = 45.5 ;

    std::cout << "Neighbors within radius search at (" << searchPoint.x
        << " " << searchPoint.y
        << " " << searchPoint.z
        << ") with radius=" << radius << std::endl;


    if (kdtree.radiusSearch(searchPoint, radius, pointIdxRadiusSearch, pointRadiusSquaredDistance) > 0)
    {
        int point_count = 0;
        for (size_t i = 0; i < pointIdxRadiusSearch.size(); ++i)
          {
            std::cout << "    " << cloud->points[pointIdxRadiusSearch[i]].x
            << " " << cloud->points[pointIdxRadiusSearch[i]].y
            << " " << cloud->points[pointIdxRadiusSearch[i]].z
            << " (distance: " << sqrt(pointRadiusSquaredDistance[i]) << ")" << std::endl;
            point_count++;
          }
        std::cout<<"There are "<<point_count<<" point cloud in "<<radius<<" radius"<<std::endl;
    }
    

    return 0;
}