# public-bucket

## 使用jsdelivr cdn

在浏览器中手动将github资源配置到jsdelivr中

以资源`https://raw.githubusercontent.com/jankiny/public-bucket/blog/img/avatar.png`为例

jsdeliver cdn的地址为
```url
# 替换模板https://cdn.jsdelivr.net/gh/${{ github.repository }}@${{ branch }}}/${file}"中的内容
https://cdn.jsdelivr.net/gh/jankiny/public-bucket@blog/img/avatar.png
```
