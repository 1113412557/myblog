<%--
  Created by IntelliJ IDEA.
  User: vansl
  Date: 18-3-19
  Time: ����5:15
  To change this template use File | Settings | File Templates.
--%>
<%@ page import="java.io.File"%>
<%@ page import="java.io.IOException"%>
<%@ page contentType="text/html;charset=GB2312" language="java" %>
<html>
    <head><title>�����ļ�Ŀ¼</title>
</head>
<body>
<%!
    public   void listDirectory(String directory,HttpServletRequest request,JspWriter out) throws  IOException {
        File dir = new File(directory);
        if(dir.isFile())            //�ж��Ƿ����ļ���������ļ��򷵻ء�
            return;
        File [] files=dir.listFiles();        //�г���ǰĿ¼�µ������ļ���Ŀ¼
        for(int i=0;i<files.length;i++){
            if(files[i].isDirectory()) {    //�����Ŀ¼�������������Ŀ¼
                listDirectory(request.getServletContext().getRealPath("/WEB-INF/statics/share/") + files[i].getName(), request, out);
            }
            out.println( "<a href=\"/share/"+files[i].getName()+"\">"+files[i].getName()+"</a></br>");    //�����Ŀ¼�����ļ�������
        }
    }
%>
<%
    //����ǰweb����Ŀ¼�ṹ���������̨
    out.println("--------------------------------------------------------------------------------------------------------------------------------</br>");
    listDirectory(request.getServletContext().getRealPath("/WEB-INF/statics/share/"),request,out);
    out.println("</br>--------------------------------------------------------------------------------------------------------------------------------");
%>
</body>
</html>