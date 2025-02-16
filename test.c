#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// دالة لفحص صحة اسم المتغير
int is_valid_identifier(const char *str) {
    if (!str || (!isalpha(str[0]) && str[0] != '_'))  
        return 0; // يجب أن يبدأ بحرف أو "_"

    for (int i = 1; str[i] && str[i] != '='; i++) {
        if (!isalnum(str[i]) && str[i] != '_')  
            return 0; // يجب أن يحتوي على أحرف، أرقام، أو "_"
    }
    return 1; 
}

// دالة لإضافة متغير بيئي إلى Minishell
void add_env_var(char *input) {
    char *equal_sign = strchr(input, '='); // البحث عن "=" في النص
    
    if (!equal_sign) {
        printf("Variable without value, will be exported but not in env: %s\n", input);
        // أضفه إلى قائمة `export` فقط
        return;
    }

    // استخراج الاسم قبل علامة "="
    char name[256];
    strncpy(name, input, equal_sign - input);
    name[equal_sign - input] = '\0';

    if (!is_valid_identifier(name)) {
        printf("Error: '%s' is not a valid identifier\n", name);
        return;
    }

    // استخراج القيمة بعد "="
    char *value = equal_sign + 1;
    printf("Added variable: %s = %s\n", name, value);

    // هنا يمكنك إضافة المتغير إلى قائمة البيئة
}

int main() {
    // اختبارات
    add_env_var("valid_name=123");         // ✅ مقبول
    add_env_var("VAR_WITH_UNDERSCORE=abc"); // ✅ مقبول
    add_env_var("_leading_underscore=ok"); // ✅ مقبول
    add_env_var("mixedCase123=hello");     // ✅ مقبول
    
    add_env_var("NO_VALUE=");             // ✅ مسموح، لكن القيمة ستكون فارغة
    add_env_var("KEY_ONLY");              // ⚠️ سيتم تصديره لكنه لن يظهر في env
    add_env_var("NO_EQUALS  ");           // ⚠️ مسموح بدون "=" لكنه لن يكون في env
    
    add_env_var("1invalidStart=wrong");   // ❌ خطأ لأنه يبدأ برقم
    add_env_var("wrong-char$=bad");       // ❌ خطأ لاحتوائه على رمز غير مسموح
    add_env_var("white space=oops");      // ❌ خطأ لاحتوائه على مسافة في الاسم
    add_env_var("equal==double=bad");     // ✅ سيتم التعامل مع القيمة كنص "double=bad"
    add_env_var("var1=85 var2=65");
    add_env_var("v@r3=bb var4=aa");
    add_env_var("var5=qw v@r6=00");
    add_env_var("   TRIM_ME  =   45   "); // ✅ سيتم تنظيف المسافات
    add_env_var("   =missing_key  ");     // ❌ خطأ لأن الاسم مفقود
    add_env_var("=bad");                  // ❌ خطأ لأن الاسم غير موجود

    return (0);
}
