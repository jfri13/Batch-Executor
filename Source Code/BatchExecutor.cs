/*
 * Title: Batch Executor
 * Language: C#
 * Version: 1.0
 */
using System;
using System.Diagnostics;
using System.Globalization;
using System.IO;
using System.Text.RegularExpressions;

namespace BatchExecutor
{
    class BatchExecutor
    {
        static void Main(string[] args)
        {
            string batFullpath = Regex.Replace(System.Reflection.Assembly.GetExecutingAssembly().Location, @"(?<=\.)exe$", "BAT");

            //파일이 있다면 IF FILE EXISTS
            if (File.Exists(batFullpath))
            {
                Process.Start(batFullpath); //실행부 RUN BATCH FILE
            }
            else //에러메세지 ERROR MESSAGE
            {
                string path = Path.GetDirectoryName(batFullpath);
                string name = Path.GetFileName(batFullpath);

                //한글
                if (CultureInfo.CurrentCulture.Name.Split('-')[0].Equals("ko"))
                {
                    Console.WriteLine("\"" + path + "\"에 \"" + name + "\"이 없습니다.");
                    Console.WriteLine("계속하려면 아무 키나 누르십시오 . . .");
                    Console.ReadKey(); // PAUSE
                    Environment.Exit(0);
                }
                //English
                Console.WriteLine("There is no \"" + name + "\" in " + "\"" + path + "\".");
                Console.WriteLine("Press any key to continue . . .");
                Console.ReadKey(); // PAUSE
            }
        }
    }
}
