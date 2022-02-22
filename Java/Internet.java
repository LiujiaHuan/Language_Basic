import java.net.*;
import java.io.*;
public class URL_Stream_read
{
    public static void main(String [] args)
    {
        try//捕获异常
        {
            URL url = new URL("http://www.baidu.com");//创建url
            URLConnection urlConnection = url.openConnection();//创建URlconnection类并调用openConnection()方法打开一个URL连接，并运行客户端访问资源
            HttpURLConnection connection = null;//用来保存HTTP协议的URL, openConnection() 方法返回 HttpURLConnection 对象
            if(urlConnection instanceof HttpURLConnection)//验证是否为http类型返回对象
            {
                connection = (HttpURLConnection) urlConnection;//保存openConnection返回的http协议对象
            }
            else
            {
                System.out.println("请输入 URL 地址");
                return;
            }
            BufferedReader in = new BufferedReader(
                    new InputStreamReader(connection.getInputStream()));//利用InputStreamReader解决解码问题，从字节流变成字符流，防止乱码
            
            String urlString = "";//保存全部内容
            String current;//用来保存每一行的内容
            while((current = in.readLine()) != null)
            {
                urlString += current;//循环读入
            }
            //System.out.println(urlString);
            System.out.println(flag);
        }catch(IOException e)
        {
            e.printStackTrace();
        }
    }
}
