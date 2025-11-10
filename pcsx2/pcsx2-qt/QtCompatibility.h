// SPDX-FileCopyrightText: 2024 PCSX2 Dev Team
// SPDX-License-Identifier: GPL-3.0+

#pragma once

#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>

/// layout->setRowVisible but compatible with older Qt
static inline void setFormRowVisible(QFormLayout* layout, int idx, bool visible)
{
#if QT_VERSION >= QT_VERSION_CHECK(6, 4, 0)
	layout->setRowVisible(idx, visible);
#else
	if (QLayoutItem* item = layout->itemAt(idx, QFormLayout::LabelRole))
		item->widget()->setVisible(visible);
	if (QLayoutItem* item = layout->itemAt(idx, QFormLayout::FieldRole))
		item->widget()->setVisible(visible);
#endif
}

#if QT_VERSION < QT_VERSION_CHECK(6, 7, 0)
template <typename Ctx, typename T>
static inline void connectCheckStateChanged(QCheckBox* check, const Ctx *context, void (Ctx::*slot)(T))
{
	static_assert(std::is_same_v<T, int> || std::is_same_v<T, Qt::CheckState>);
	check->connect(check, &QCheckBox::stateChanged, context, reinterpret_cast<void(Ctx::*)(int)>(slot));
}
template <typename Ctx>
static inline void connectCheckStateChanged(QCheckBox* check, const Ctx *context, void (Ctx::*slot)())
{
	check->connect(check, &QCheckBox::stateChanged, context, slot);
}
template <typename Func>
static inline void connectCheckStateChanged(QCheckBox* check, QObject *context, Func&& slot)
{
	if constexpr (std::is_invocable_v<Func> || std::is_invocable_v<Func, int>)
	{
		check->connect(check, &QCheckBox::stateChanged, context, std::forward<Func>(slot));
	}
	else
	{
		check->connect(check, &QCheckBox::stateChanged, context, [slot = std::forward<Func>(slot)](int state){
			slot(static_cast<Qt::CheckState>(state));
		});
	}
}
#else
template <typename Func>
static inline void connectCheckStateChanged(QCheckBox* check, const typename QtPrivate::ContextTypeForFunctor<Func>::ContextType *context, Func&& slot)
{
	check->connect(check, &QCheckBox::checkStateChanged, context, std::forward<Func>(slot));
}
#endif
