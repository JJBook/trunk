/***********************************************************************
*   Copyright (C) 2016 pilot-lab.inc All rights reserved.
*   
*   @file:       main.c
*   @brief:      
*   @author:     Pilot labs
*   @maintainer: frank.fu@pilot-lab.com.cn
*   @version:    1.0
*   @date:       2016-05-09
*   
***********************************************************************/
#include "file.h"
#include "log.h"
#include <stdio.h>
#include <sys/vfs.h>
#include <errno.h>
#include "tfcard.h"

int main(int argc, char** argv)
{
	SIZE_S size;

	if (argc < 2)
	{
		printf("usage: ./%s /mnt/mmcblk0", argv[1]);	
		return -1;
	}
	
	getTotalSize(argv[1], &size);
	printf("tatal size =%.2f, type=%x\n", size.m_fSize, size.m_eSizeType);

	getUsedSize(argv[1], &size);
	printf("used size =%.2f, type=%x\n", size.m_fSize, size.m_eSizeType);

	getAvailableSize(argv[1], &size);
	printf("available size =%.2f, type=%x\n", size.m_fSize, size.m_eSizeType);

	float fPercent = 0.0;
	getUsedPercent(argv[1], &fPercent);
	printf("percent =%.2f\n", fPercent);

	return 0;
}

#if 0
int main(int argc, char** argv)
{

	if (-1 == tfcard_is_exist(TFCARDPATH))
	{
		PL_LOGE(PL_TAG, "%s is not exist\n", TFCARDPATH);
		return -1;
	}

	struct statfs disk_info;

	if (statfs(TFCARDPATH, &disk_info) == -1)
    {
		PL_LOGE(PL_TAG, "Failed to get file disk infomation,errno:%u, reason:%s\n", errno, strerror(errno));
		return -1;
	}
		
	unsigned long total_size = (disk_info.f_blocks>>10) * (disk_info.f_bsize>>10);
	unsigned long available_size = (disk_info.f_bavail >> 10)* (disk_info.f_bsize >> 10);
	unsigned long free_size = (disk_info.f_bfree >> 10)* (disk_info.f_bsize >> 10);
	unsigned long used_size = (disk_info.f_blocks - disk_info.f_bavail)
	printf("disk_info.f_bsize >> 10=%lu\n",disk_info.f_bsize >> 10);
	printf("disk_info.f_bavail >> 10=%lu\n",disk_info.f_bavail >> 10 );
	printf("disk_info.f_bfree >> 20=%lu\n",disk_info.f_bfree >> 20);

	//���ÿ����ĳ��ȣ�linux���ڴ��Ϊ4KB
	printf("block size: %ld bytes\n", disk_info.f_bsize);
	//��������
	printf("total data blocks: %ld \n", disk_info.f_blocks);
	//���path���ڴ��̵Ĵ�С
	printf("total file disk size: %ld MB\n",total_size);
	//�����root�û������õĴ��̿ռ��С
	printf("avaiable size: %ld MB\n",available_size);
	//���Ӳ�̵�����ʣ��ռ�
	printf("free size: %ld MB\n",free_size);
	//����������ļ��ڵ����
	printf("total file nodes: %ld\n", disk_info.f_files);
	//��������ļ��ڵ����
	printf("free file nodes: %ld\n", disk_info.f_ffree);
	//����ļ�����󳤶�
	printf("maxinum length of file name: %ld\n", disk_info.f_namelen);

	return 0;

}
#endif
