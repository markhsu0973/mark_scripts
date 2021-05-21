#include <iostream>
#include <pcl/point_types.h>
#include <pcl/features/normal_3d.h>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/pcl_visualizer.h>

int main(int argc, char **argv) 
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::io::loadPCDFile("table_scene_lms400.pcd", *cloud);

    //create the normal estimation class, and pass the input dataset to it
    pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> ne;
    ne.setInputCloud(cloud);

    //create an empty kdtree representation, and pass it to the normal estimation object
    //its content will be filled inside the object, based on the given input dataset(as no other search surface is given)
    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>());
    ne.setSearchMethod(tree);

    //Output datasets
    pcl::PointCloud<pcl::Normal>::Ptr cloud_normals (new pcl::PointCloud<pcl::Normal>);

    //use all neighbours in a sphere of radius 3cm
    ne.setRadiusSearch(0.03);

    //compute the features
    //cloud_normals->points.size() should have the same size as the input cloud->points.size
    ne.compute(*cloud_normals);

    //
    for(int ix=0;ix<cloud_normals->points.size();ix++)
    {
      if(isnan(cloud_normals->points[ix].normal_x)|| isnan(cloud_normals->points[ix].normal_y))
        continue;
      double normals_x = cloud_normals->points[ix].normal_x;
      double normals_y = cloud_normals->points[ix].normal_y;
      double normals_z = cloud_normals->points[ix].normal_x;
      // double normals_xy = sqrt(normals_x*normals_x + normals_y*normals_y);
      // double normals_xy_total = normals_xy_total + normals_xy;
      std::cout<<"x "<<normals_x<<" y = "<<normals_y<<" z = "<<normals_z;
    }
    
    //normal visualization
    pcl::visualization::PCLVisualizer viewer("PCL viewer");
    viewer.setBackgroundColor(0.0, 0.0, 0.0);
    viewer.addPointCloudNormals<pcl::PointXYZ, pcl::Normal>(cloud, cloud_normals);

    while(!viewer.wasStopped())
    {
      viewer.spinOnce();
    }

    return 0;
}