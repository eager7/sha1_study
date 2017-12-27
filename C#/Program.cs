using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
using System.IO;

class Program
{
    static void Main(string[] args)
    {
        Console.WriteLine("Hello World!");
        byte[] key = {};
        byte[] challenge = { 0,0,0,0,  0, 0, 0, 0,   0, 0, 0, 0,   0, 0, 0, 0,   0, 0, 0x01, 0x23 };
       
        var tmp = new byte[36];
        key.CopyTo(tmp, 0);
        challenge.CopyTo(tmp, 16);
        System.Console.WriteLine("tmp:" + BitConverter.ToString(tmp));

        var hash = tmp.Aggregate("", (s, e) => s + String.Format("{0:x2}", e), s => s);
        System.Console.WriteLine("input:" + hash);

        var per2 = SHA1.Create().ComputeHash(tmp);
        hash = per2.Aggregate("", (s, e) => s + String.Format("{0:x2}", e), s => s);
        System.Console.WriteLine("sha1:" + hash);

        var tmp2 = new byte[36];
        key.CopyTo(tmp2, 0);
        per2.CopyTo(tmp2, 16);
        System.Console.WriteLine("tmp2:" + BitConverter.ToString(tmp2));

        hash = tmp2.Aggregate("", (s, e) => s + String.Format("{0:x2}", e), s => s);
        System.Console.WriteLine("input2:" + hash);

        var result = SHA1.Create().ComputeHash(tmp2).Aggregate("", (s, e) => s + String.Format("{0:x2}", e), s => s);
        System.Console.WriteLine("result:" + result);
    }
}