#include <iostream>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/console/parse.h>

class pcd_prcessing{
  
  public:
    pcd_prcessing()
    //初始化指標
    : cloud(new pcl::PointCloud<pcl::PointXYZRGB>) {}

    ~pcd_prcessing() {}
  void
  pcd_reading(const std::string& pcd_file_name)
  {
    pcl::PCDReader reader;
    // Replace the path below with the path where you saved your file
    reader.read (pcd_file_name, *cloud); // Remember to download the file first!
    if(cloud->points.size ()== 0)
    {
      std::cout<<"The cloud is empty"<<std::endl;
      return ;
    }
    else
    {
      std::cout<<"read pcd file successful"<<std::endl;
    }
  }
  void
  pcd_viewer(){
    pcl::visualization::CloudViewer viewer("Cloud Viewer");
    viewer.showCloud(cloud);
    while (!viewer.wasStopped()){ };
  }

  private:
    //宣告指標
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud ;
};


int
main (int argc, char** argv)
{
  pcd_prcessing pp;
  pp.pcd_reading("teacup.pcd");
  pp.pcd_viewer();
  return (0);
}
