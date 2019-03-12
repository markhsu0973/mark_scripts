#!/usr/bin/python
#http://192.168.100.50/snippets/18
import rosbag_pandas
import matplotlib.pyplot as plt

df = rosbag_pandas.bag_to_dataframe('agv18.bag')


# for c in df.columns:
#     print c, df[c].min(),  df[c].max()

# df2 = df.fillna(method='pad')
#
# r_driv = df2['motor_odom_R__data']
# l_driv = df2['motor_odom_L__data']

# plt.figure()

#df.loc[:, ['motor_odom_L__data', 'motor_odom_R__data']].plot(style='.')

#plt.show()

def normalize(ser):
    return (ser - ser.mean()) / ser.std()

df2 = df

r_driv = df2['motor_odom_R__data']
l_driv = df2['motor_odom_L__data']


df2['motor_odom_R__data_driv'] = normalize(r_driv)
df2['motor_odom_L__data_driv'] = normalize(l_driv)
#
# # plt.figure()
#
df2.loc[:, ['motor_odom_R__data_driv', 'motor_odom_L__data_driv']].plot(style='.')
plt.autoscale(enable=True, axis='both', tight=None)
plt.show()

# df2 = df

# r_driv = df2['motor_odom_R__data']
# l_driv = df2['motor_odom_L__data']

# df2['motor_odom_R__data_driv'] = normalize(r_driv)
# df2['motor_odom_L__data_driv'] = normalize(l_driv)

# plt.figure()

# df2.loc[:, ['battery_arriving__data', 'cmd_vel__data']].plot(style='.')
# plt.autoscale(enable=True, axis='both', tight=None)
# plt.show()