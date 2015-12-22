#include <opencv2/opencv.hpp>
// Extract_InfoDlg.h : ͷ�ļ�
//

#pragma once


// CExtract_InfoDlg �Ի���
class CExtract_InfoDlg : public CDialogEx
{
// ����
public:
	CExtract_InfoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_EXTRACT_INFO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void ShowImage(IplImage* img, unsigned int ID);
	//���ű���
	float  ratio;
	afx_msg void OnBnClickedOpenpic();
	//·��
	CString mPath;
	//ԴͼƬ
	cv::Mat sourceImg;
	int Pic_Size;
	afx_msg void OnBnClickedExtractinfo();
	afx_msg void EnCode2();
	CString code_info;
	afx_msg void DeCode();
	CFont m_font;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
//	afx_msg void OnStnClickedTitle();
};
