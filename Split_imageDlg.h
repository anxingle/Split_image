#include <opencv2/opencv.hpp>
// Extract_InfoDlg.h : 头文件
//

#pragma once


// CExtract_InfoDlg 对话框
class CExtract_InfoDlg : public CDialogEx
{
// 构造
public:
	CExtract_InfoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_EXTRACT_INFO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void ShowImage(IplImage* img, unsigned int ID);
	//缩放比例
	float  ratio;
	afx_msg void OnBnClickedOpenpic();
	//路径
	CString mPath;
	CString mPath1;
	CString mPath2;
	CString mPath3;
	CString mPath4;
	//源图片
	cv::Mat sourceImg;
	cv::Mat sourceImg1;
	cv::Mat sourceImg2;
	cv::Mat sourceImg3;
	cv::Mat sourceImg4;
	//提取通道后
	IplImage *rImg, *bImg, *gImg, *xImg;
	int Pic_Size;
	afx_msg void OnBnClickedExtractinfo();
//	afx_msg void EnCode2();
	CString code_info;
//	afx_msg void DeCode();
	CFont m_font;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
//	afx_msg void OnStnClickedTitle();
	unsigned char RSA_decode(unsigned char pixes);
	void EncodeImg(IplImage*);
	IplImage* DncodeImg(IplImage*);
	afx_msg void OnBnClickedDecode();
	afx_msg void OnBnClickedOpencode();
	afx_msg void OnBnClickedSave();
};
