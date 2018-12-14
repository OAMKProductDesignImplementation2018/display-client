#include "organization.h"

Organization& Organization::getInstance() {
    static Organization organization;
    return organization;
}
