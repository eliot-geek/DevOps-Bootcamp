#!/bin/bash
TELEGRAM_BOT_TOKEN="7213980038:AAERdgYaJR4qbj_e8Izj8XPQWkrpsRkqpaU"
TELEGRAM_USER_ID="877280567"
URL="https://api.telegram.org/bot$TELEGRAM_BOT_TOKEN/sendMessage"

TIME="10"
TEXT="Deploy status: $1%0A%0AProject:+$CI_PROJECT_NAME%0AURL:+$CI_PROJECT_URL/pipelines/$CI_PIPELINE_ID/%0ABranch:+$CI_COMMIT_REF_SLUG"

if [ $CI_JOB_STATUS == 'success' ]; then
    echo 'Integretion tests passed successfully'
    curl -s -X POST $URL \
    -d chat_id=$TELEGRAM_USER_ID \
    -d text="The stages of CI for `$CI_PROJECT_NAME` were successful!";
else
    echo 'Integration tests failed'
    curl -s -X POST $URL \
    -d chat_id=$TELEGRAM_USER_ID \
    -d text="The CI stages for `$CI_PROJECT_NAME` did not pass.";
fi
curl -s --max-time $TIME -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null