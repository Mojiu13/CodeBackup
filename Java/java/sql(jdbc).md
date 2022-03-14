jdbc：java连接数据库必备
jdbc标准 提供很多接口
jdbc代码 模板代码
## java连接数据库步骤：
1. 加载驱动包
2. 获取连接【url username pwd】
3. 基本操作
4. 释放资源
## 连接模板
```
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;


public class test{
	private String host;
	private Connection conn;//声明Connection引用
	private Statement stmt;//声明Statement引用
	private ResultSet rs;//声明结果集引用
	
	//数据库连接的方法
		public void initialConnection()
		{
			System.out.printf("连接数据库\n");
			try
			{
				Class.forName("com.mysql.cj.jdbc.Driver"); //jdbc mysql连接驱动
				conn=DriverManager.getConnection("jdbc:mysql://localhost:3306/java_chap02?useUnicode=true&characterEncoding=utf-8&useSSL=false&serverTimezone=GMT","root","123");
				stmt=conn.createStatement();
			}
			catch(SQLException e)
			{
				System.out.println("SQL语句出错--->");
				e.printStackTrace();
			}
			catch(ClassNotFoundException e)
			{
				System.out.println("没有发现MySQL驱动--->");
				e.printStackTrace();
			}
		}

		public void closeConn()
		{
			try
			{
				if(rs!=null){rs.close();}
				if(stmt!=null){stmt.close();}
				if(conn!=null){conn.close();}
			}
			catch(SQLException e)
			{
				System.out.println("关闭连接出现异常--->");
				e.printStackTrace();
			}
		}
		
		public static void main(String args[]){
			test tem=new test();
			String[] message=new String[3];
			String stu_id="103317012121";
			try
			{   //初始化数据库连接并更改密码
				tem.initialConnection();
				System.out.printf("*****数据库连接成功*****\n");
				String sql="select stu_id,stu_name,stu_gender from student where stu_id='"+stu_id+"'";
						
				tem.rs=tem.stmt.executeQuery(sql);
				if(tem.rs.next()){
					message[0]=tem.rs.getString(1);
					message[1]=new String(tem.rs.getString(2).getBytes("gb2312"));
					message[2]=new String(tem.rs.getString(3).getBytes("gb2312"));
				}
				tem.closeConn();//关闭数据库连接
			}
			catch(Exception ea)
			{
				ea.printStackTrace();
			}
			
			for(int i=0;i<3;i++)
			System.out.printf(message[i]+"\n");
		}
}

```


运用java调用sql语句模板
** *注意 在结果查询后 需要调用 result.next()至少一次将指针指向第一个数据 以便之后利用 * **

引用：在对结果集ResultSet进行操作之前，一定要先用ResultSet.next()将指针移动至结果集的第一行

看看API对next()方法的描述：

......
将光标从当前位置向前移一行。ResultSet 光标最初位于第一行之前；第一次调用 next 方法使第一行成为当前行；第二次调用使第二行成为当前行，依此类推。 
当调用 next 方法返回 false 时，光标位于最后一行的后面
*注意 ResultSet 中封装的并不是我们查询到的所有的结果集， 而是返回了查询到的结果  
集的数据库游标。 通过 ResultSet 中的 next()方法操作游标的位置获取结果集*
```
package com.learn.jdbc.chap05;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.List;

import com.learn.jdbc.model.Album;
import com.learn.jdbc.util.DbUtil;
/**
 * 使用ResultSet结果集（数据查询）
 * @author Administrator
 *
 */
public class Demo1 {

    private static DbUtil dbUtil=new DbUtil();

    private static void listAlbum() throws Exception{
        Connection con = dbUtil.getCon();
        String sql="select * from sp_album";
        PreparedStatement pstmt = con.prepareStatement(sql);
        ResultSet rs = pstmt.executeQuery(); // 返回结果集 ResultSet
        while(rs.next()){
            // 下面的写法 在工作中 很少用
            int id=rs.getInt(1);
            String name=rs.getString(2);
            int uid=rs.getInt(3);
            long time=rs.getLong(4);
            System.out.println("编号："+id+",名称："+name+",会员id："+uid+",添加时间："+time);
            System.out.println("-----------------------");
        }

    }

    private static void listAlbum2() throws Exception{
        Connection con = dbUtil.getCon();
        String sql="select * from sp_album";
        PreparedStatement pstmt = con.prepareStatement(sql);
        ResultSet rs = pstmt.executeQuery(); // 返回结果集 ResultSet
        while(rs.next()){
            // 下面的写法 在工作中 经常这么写
            int id=rs.getInt("id");
            String name=rs.getString("name");
            int uid=rs.getInt("uid");
            long time=rs.getLong("add_time");
            System.out.println("编号："+id+",名称："+name+",会员id："+uid+",添加时间："+time);
            System.out.println("-----------------------");
        }

    }

    private static List<Album> listAlbum3() throws Exception{
        List<Album> albumList = new ArrayList<Album>();

        Connection con = dbUtil.getCon();
        String sql="select * from sp_album";
        PreparedStatement pstmt = con.prepareStatement(sql);
        ResultSet rs = pstmt.executeQuery(); // 返回结果集 ResultSet
        while(rs.next()){
            // 下面的写法 在工作中 经常这么写
            int id=rs.getInt("id");
            String name=rs.getString("name");
            int uid=rs.getInt("uid");
            long time=rs.getLong("add_time");

            Album ab=new Album(id, name, uid, time);
            albumList.add(ab);
        }

        return albumList;
    }

    public static void main(String[] args) throws Exception {
        /*listAlbum();
        System.out.println("=============================================");
        listAlbum2();*/
        List<Album> abInfo = listAlbum3();
        for(Album abm:abInfo){ // 此处的abm默认输出是调用父类的toString方法，要输出自定义信息，需要重写toString方法
            System.out.println(abm);
            //System.out.println(abm.getName());
        }
    }
}
```

statement查询数据方法
```
private static void selectDepartmentsById(int department_id) {
        String sql = "select * from departments where department_id = " + department_id;
        Connection connection = DBUtil.getConnection();
        Statement statement = null;
        ResultSet resultSet = null;
        try {
            statement = connection.createStatement();
            resultSet = statement.executeQuery(sql);
            while (resultSet.next()) {
                String department_name = resultSet.getString("department_name");
                System.out.println("department_name = " + department_name);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            DBUtil.close(resultSet, statement, connection);
        }
    }
}
```
PreparedStatement查询数据
```
Class.forName("com.mysql.jdbc.Driver");  
  
//2. 获取连接【url username pwd】  
Connection conn = DriverManager.getConnection  
 ("jdbc:mysql://localhost:3306/cdlg?useSSL=false", "root", "0514");  
String name="admin";  
String psw="111";  
  
String sql="SELECT * FROM user WHERE uname=?";  
//3. 基本操作  
PreparedStatement pst=null;  
pst= conn.prepareStatement(sql);  
pst.setString(1,name);  
ResultSet qs=null;  
qs=pst.executeQuery();  
String pas=null;  
qs.next();  
pas=qs.getString(3);  
String pass=null;  
System.out.println(pas);  
//4. 释放资源  
qs.close();  
pst.close();  
conn.close();
```