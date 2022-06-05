//如果没有定义 _SECRETS_INT_H 则定义 _SECRETS_INT_H
#ifndef _SECRETS_INT_H
#define _SECRETS_INT_H

//枚举类型 field_type
enum field_type
{
  PRIVATE,
  MODULUS,
  PUBLIC_E
};
//结构体 fld
struct fld
{
  const char *name;
  enum field_type type;
  size_t offset;
};

//向外暴露结构体
extern const struct fld RSA_private_field[];
//向外暴露变量
extern const int RSA_private_field_count;

#endif /* _SECRETS_INT_H */
