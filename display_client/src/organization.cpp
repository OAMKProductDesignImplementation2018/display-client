#include "organization.h"

Organization& Organization::getInstance() {
    static Organization organization;
    return organization;
}

void Organization::setRestaurantName(const QString name) {
    _restaurantName = name;
    emit restaurantNameUpdated(_restaurantName);
}

void Organization::setOrganizationName(const QString name) {
    _organizationName = name;
    emit organizationNameUpdated(_organizationName);
}
