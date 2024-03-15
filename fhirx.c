#include "fhirx.h"
#include "utils/json.h"

PG_FUNCTION_INFO_V1(fhirx_resource_type);
Datum
fhirx_resource_type(PG_FUNCTION_ARGS)
{
    text *json_text = PG_GETARG_TEXT_PP(0);
    JsonObject *json_obj = (JsonObject *) pq_nl2json(VARDATA_ANY(json_text), VARSIZE_ANY_EXHDR(json_text));

    char *resource_type = NULL;

    if (json_obj != NULL)
    {
        JsonValue *resource_type_value = get_json_object_value(json_obj, "resourceType");
        if (resource_type_value != NULL && resource_type_value->type == jvString)
        {
            resource_type = pstrdup(resource_type_value->val.string.val);
        }
    }

    if (resource_type == NULL)
    {
        PG_RETURN_NULL();
    }
    else
    {
        PG_RETURN_TEXT_P(cstring_to_text(resource_type));
    }
}