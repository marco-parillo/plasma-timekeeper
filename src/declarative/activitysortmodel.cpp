/*
    Copyright 2016 Jan Grulich <jgrulich@redhat.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) version 3, or any
    later version accepted by the membership of KDE e.V. (or its
    successor approved by the membership of KDE e.V.), which shall
    act as a proxy defined in Section 6 of version 3 of the license.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "activitysortmodel.h"

#include <KLocalizedString>

const static QString OTHER_APPLICATIONS_NAME = i18n("other applications");

ActivitySortModel::ActivitySortModel(QObject* parent)
    : QSortFilterProxyModel(parent)
{
    setDynamicSortFilter(true);
    sort(0, Qt::DescendingOrder);
}

ActivitySortModel::~ActivitySortModel()
{
}

bool ActivitySortModel::filterAcceptsRow(int source_row, const QModelIndex& source_parent) const
{
    // TODO maybe
    return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
}

bool ActivitySortModel::lessThan(const QModelIndex& left, const QModelIndex& right) const
{
    const QString leftName = sourceModel()->data(left, ActivityModel::ActivityNameRole).toString();
    const QString rightName = sourceModel()->data(right, ActivityModel::ActivityNameRole).toString();
    const QTime leftTime = sourceModel()->data(left, ActivityModel::ActivityTimeRole).toTime();
    const QTime rightTime = sourceModel()->data(right, ActivityModel::ActivityTimeRole).toTime();

    if (leftName == OTHER_APPLICATIONS_NAME) {
        return true;
    } else if (rightName == OTHER_APPLICATIONS_NAME) {
        return false;
    }

    return leftTime < rightTime;
}