# 关于Inception

MySQL语句的审核，在业界都已经基本被认同了，实际上也是对MySQL语句写法的统一化，标准化，而之前的人工审核，针对标准这个问题其实是很吃力的，标准越多，DBA越累，开发也越累。
那么在这个都追求自动化运维的时代，审核也必须要跟上步伐，因此Inception诞生了。而Inception可以做的工作远不止是一个自动化审核工具，同时还具备执行，生成对影响数据的回滚语句（类似闪回的功能），这样一条龙服务的工具，将会给DBA的工作带来翻天覆地的变化，DBA从此就从繁重的审核、登上去执行，出错了很难回滚（如果提前没有备份的话）的被动局面解放了出来，突然发现，做DBA原来可以这么轻松，工作可以不饱和了，那就有更多的自由时间学习、进一步向自动化运维平台的实现等更智能化的方向去发展，是具有里程碑意义的。

## 文档地址：

https://inception-document.readthedocs.io/zh_CN/latest/

## Docker

https://hub.docker.com/r/hhyo/inception

#### 配置文件准备，参考配置（inc.cnf）
```
[inception]
general_log=1
general_log_file=inception.log
port=6669
socket=/tmp/inc.socket
character-set-client-handshake=0
character-set-server=utf8
inception_remote_system_password=root
inception_remote_system_user=wzf1
inception_remote_backup_port=3306
inception_remote_backup_host=127.0.0.1
inception_support_charset=utf8,utf8mb4
inception_enable_nullable=0
inception_check_primary_key=1
inception_check_column_comment=1
inception_check_table_comment=1
inception_osc_on=OFF
inception_osc_bin_dir=/usr/bin
inception_osc_min_table_size=1
inception_osc_chunk_time=0.1
inception_enable_blob_type=1
inception_check_column_default_value=1
```
#### 指定配置文件和端口启动
```
docker run --name inception -v /local_path/inc.cnf:/etc/inc.cnf  -p 6669:6669 -dti hhyo/inception
```
#### 访问
```
mysql -hxxxx -P6669
```

## WEB平台

https://github.com/hhyo/archery
