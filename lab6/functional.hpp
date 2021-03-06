#ifndef DD_H
#define DD_H
#include <QBitArray>
#include <QTextCodec>
#include <iostream>
#include <QDataStream>
#include <QDebug>
#include<math.h>
#include<conio.h>

std::string XOR(std::string s1, std::string s2)
{
    std::string result = "";

    for (int i = 0; i < s1.length(); i++)
    {
        if (s1[i] ^ s2[i])
             result += "1";
         else
             result += "0";
    }
    return result;
}
std::string Shift(std::string str, int shift)
{
    for (int i = 0; i < shift; i++)
    {
        str = str + str[0];
        str = str.substr(1, str.length());
    }

    return str;
}
std::string f(std::string s1, std::string s2)
 {
     return XOR(XOR(Shift(s1,1), Shift(s1,5) ),s2);
 }
std::string EncodeDES_One_Round(std::string input, std::string key)
{
    std::string L = input.substr(0, input.length() / 2);
    std::string R = input.substr(input.length() / 2, input.length() / 2);

    return (R + XOR(L, f(R, key)));
}


std::string DecodeDES_One_Round(std::string input, std::string key)
{
    std::string L = input.substr(0, input.length() / 2);
    std::string R = input.substr(input.length() / 2, input.length() / 2);

    return (XOR(f(L, key), R) + L);
}

QBitArray by2bi(QByteArray data)
{
    QBitArray bits(data.count()*8);
    for (int i = 0; i < data.count(); ++i) {
        for (int b = 0; b < 8; b++) {
            bits.setBit( i * 8 + b , data.at(i) & (1<<  b) );
        }
    }
    return bits;
}

QByteArray convertbybyte(QBitArray bits)
{
    QByteArray bytes;
    for(int b=0; b<bits.count(); ++b){
        bytes[b/8] = (bytes.at(b/8) | ((bits[b]?1:0)<<(b%8)));
    }
    return bytes;
}
std::string incript(QString bits_line)
{
    std::string key = "10100101";
    std::string str = bits_line.toLocal8Bit().constData();
    std::string Block="0000000000000000";
    int mod = (bits_line.size() / 16)*16;
    for(int j=0;j<mod; j+=16)
    {
        for(int i = 0; i < 16; i++){
            Block[i] = str[i+j];
        }
        Block = DecodeDES_One_Round(DecodeDES_One_Round(DecodeDES_One_Round(Block, key), key),key );
        for(int i = 0; i < 16; i++){
            str[i+j] = Block[i];
        }
    }
    return str;
}
std::string decript(QString bits_line)
{
    std::string key = "10100101";
    std::string str = bits_line.toLocal8Bit().constData();
    std::string Block="0000000000000000";
    int mod = (bits_line.size() / 16)*16;
    for(int j=0;j<mod; j+=16)
    {
        for(int i = 0; i < 16; i++){
            Block[i] = str[i+j];
        }
        Block = EncodeDES_One_Round(EncodeDES_One_Round(EncodeDES_One_Round(Block, key), key),key );
        for(int i = 0; i < 16; i++){
            str[i+j] = Block[i];
        }
    }
    return str;
}

QString bi2str(QBitArray bits)
{
    QString tempStr = "";
    for (int i = 0; i < bits.count(); i++) {
        tempStr+=bits.at(i)?'1':'0';
    }
    return tempStr;
 }

#endif // DD_H
